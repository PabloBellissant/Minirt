# MiniRT — Full Codebase Analysis Notes

> Complete file-by-file analysis of the miniRT project, produced by reading
> every file in the repository. This is the source material for the
> documentation.

---

## 1. Project Overview

miniRT is a GPU-accelerated ray tracing renderer written in C with OpenCL
kernels. It started as a 42 School graphics project (basic CPU ray tracer
with Phong shading and simple primitives) and evolved into a full physically
based rendering pipeline with:

- 6 rendering modes (wireframe, Phong, PBR, Monte Carlo, normal debug, heat map)
- OpenCL GPU acceleration for all ray tracing
- BVH acceleration structures with SAH (Surface Area Heuristic)
- Wavefront OBJ mesh loading with PBR material support
- MTL material parsing (standard PBR properties: kd, ks, ke, ns, ni, d, Pr, Pm)
- Texture maps: diffuse, normal, roughness, ambient, opacity, metalness
- Interactive 6-DOF camera with depth-of-field (thin lens model)
- Progressive accumulation rendering for noise reduction
- Multiple BVH branching factors (BVH2, BVH4, BVH8)
- Chromatic dispersion in Monte Carlo mode

**Authors:** Aubry Richard Jaurel & Bellissant Pablo (42 Lyon)
**Language:** C (gnu11) + OpenCL C
**Lines of code:** ~9,300 (125 .c + 8 .h + 14 .cl)

---

## 2. Object Hierarchy & Data Structures

### 2.1. Core Data Flow

```
t_data (top-level state)
├── t_opencl cl          — OpenCL context, queue, kernels, GPU buffers
├── t_buffers buffers    — Host-side ray/hit/accumulation buffers
├── t_params params       — render_mode, bvh_depth, bvh_color_offset, bvh_debug
├── t_keys keys           — WASD + QE roll state
├── t_mouse mouse         — yaw/pitch (target + current, smoothed)
├── t_mlx *mlx            — minilibx window/image
├── t_vec2i screen         — screen dimensions
└── t_scene scene         — the parsed scene
    ├── t_rgb ambient
    ├── t_camera camera   — position, rotation, basis vectors, FOV, DOF
    ├── t_vector objects  — all geometric objects (union type)
    ├── t_vector light    — point lights
    ├── int *planes_id
    ├── int plane_count
    ├── t_bvh_main bvh    — BVH state (AABB + sphere BVH, BVH2/4/8 variants)
    ├── t_vector texture  — loaded textures (PPM/PNG)
    ├── t_vector mat       — materials (parsed from MTL)
    ├── t_vector mtl_list  — MTL file references
    ├── t_vector obj_list  — OBJ file references
    ├── int skybox_tex     — skybox texture index (-1 if none)
    └── cl_mem spheres/triangles/planes/textures/mats/lights — GPU buffers
```

### 2.2. Object Union (t_object)

```c
typedef struct s_object {
    char           *name;
    int            mat_id;
    t_object_type  type;   // AMBIENT, CAMERA, SPHERE, PLANE, TRIANGLE, SKYBOX, MATERIAL
    float          t;      // hit distance (transient)
    union {
        t_light   light;
        t_sphere  sphere;    // pos, mat, diameter
        t_plane   plane;     // pos, normal, tangent, bitangent, mat, texture_scaling
        t_triangle triangle; // 3 vertices + precomputed edges/dot products
    };
} t_object;
```

### 2.3. Material (t_mat)

```c
typedef struct s_mat {
    char           *name;
    cl_float       ns;       // shininess (Phong specular exponent)
    cl_float3      kd;       // diffuse color
    cl_float3      ks;       // specular color
    cl_float3      ke;       // emissive color
    cl_float       opacity;  // (d in MTL) — 1=opaque, 0=transparent
    t_texture_data kd_id;    // diffuse texture map
    t_texture_data normal_id;   // normal/bump map
    t_texture_data roughness_id; // roughness map (Pr)
    t_texture_data ambient_id;  // ambient occlusion map (Ka)
    t_texture_data opacity_id;  // opacity map (map_d)
    t_texture_data metalness_id; // metalness map (Pm)
    cl_float       ni;       // index of refraction
} t_mat;
```

### 2.4. Camera (t_camera)

```c
typedef struct s_camera {
    cl_float3 pos;            // world position
    cl_float3 rot;            // Euler angles (x=pitch, y=yaw, z=roll)
    cl_float3 camera_forward; // computed basis vector
    cl_float3 camera_right;
    cl_float3 camera_up;
    cl_float3 pixel_delta_u; // per-pixel viewport step
    cl_float3 pixel_delta_v;
    cl_float3 pixel00_loc;    // top-left pixel center in world space
    cl_int    fov;           // field of view in degrees
    cl_int    frame;          // accumulation frame counter
    cl_float   lens_radius;   // DOF: lens aperture radius
    cl_float   focus_dist;    // DOF: focal distance
} t_camera;
```

### 2.5. BVH (t_bvh_main)

```c
typedef struct s_bvh_main {
    t_aabb_bvh *triangle_bvh;  // BVH2 triangle nodes
    t_aabb_bvh *sphere_bvh;    // BVH2 sphere nodes
    int         bvh_mode;      // 0=sphere BVH, 1=SAH AABB BVH
    int         sphere_bvh_size;
    int         triangle_bvh_size;
    t_aabb_bvh *triangle_bvh4; // BVH4 variants
    t_aabb_bvh *sphere_bvh4;
    t_aabb_bvh *triangle_bvh8; // BVH8 variants
    t_aabb_bvh *sphere_bvh8;
    cl_mem      sphere_gpu_bvh;   // GPU buffer handle
    cl_mem      triangle_gpu_bvh;
} t_bvh_main;
```

### 2.6. AABB BVH Node (t_aabb_bvh)

```c
typedef struct s_aabb_bvh {
    union {
        struct { cl_float3 min; cl_float3 max; };
        t_cuboid cuboid;
    };
    union {
        int next;           // skip pointer for BVH2 linear traversal
        int object;         // leaf: object index
        int children[8];    // BVH4/BVH8: child node indices
    };
    int            depth;       // 0=leaf, >0=internal
    int            skip;        // jump index for stackless traversal
    int            child_count;
    t_bvh_ary_type bvh_ary_type; // BVH2, BVH4, or BVH8
} t_aabb_bvh;
```

### 2.7. GPU Structures (gpu.cl)

The OpenCL kernels use GPU-side structs defined in `shader/include/gpu.cl`:

- `t_camera_gpu` — same as t_camera but using float3 instead of cl_float3
- `t_ray_gpu` — origin, dir, inv_dir
- `t_hit_gpu` — normal, uv, mat_id, hit_point, hit_obj, hit_type
- `t_hit_data` — kd, normal, ks, ke, reflectivity, metalness, roughness, ns, ambient, opacity, ni
- `t_mat_gpu` — same fields as t_mat but GPU-native types
- `t_sphere_gpu` — pos, mat, diameter
- `t_triangle_gpu` — 3 vertices (t_vertex with pos/uv/norm) + precomputed edges
- `t_plane_gpu` — pos, normal, tangent, bitangent, mat, texture_scaling
- `t_bvh_gpu` — min, max, depth, skip, bvh_type, children, child_count
- `t_objects` — aggregator struct passed to all intersection functions

---

## 3. Render Modes (Dispatch Table)

Defined in `src/loop.c`:

```c
static void (*render_func[])(t_data *, t_img_data *img)
    = {wireframe_render, phong_render, pbr_render,
       monte_carlo_render, normal_render, heat_render};
```

| Index | Mode | Key | Description |
|-------|------|-----|-------------|
| 0 | Wireframe | 1 | CPU rasterized debug view (BVH boxes, outlines, lights) |
| 1 | Phong | 2 | GPU Phong shading (ambient + diffuse + specular + emissive) |
| 2 | PBR | 3 | GPU PBR with reflection, Fresnel, refraction, bounces |
| 3 | Monte Carlo | 4 | GPU path tracing with accumulation, GGX, dispersion |
| 4 | Normal | 5 (-) | GPU normal visualization (normals mapped to colors) |
| 5 | Heat | 6 (=) | GPU BVH traversal depth heat map |

Keys 1-4 set render_mode directly; `+`/`-` (XK_equal/XK_minus) toggle between
modes 4 (normal) and 5 (heat) as debug modes.

### 3.1. Render Function Pattern

All GPU render modes (Phong, PBR, Monte Carlo, Normal, Heat) follow the same
pattern in their `*_render.c` files:

1. Check if camera moved or render params changed → if so, reset accumulation
   buffer to zero and recompute camera basis vectors
2. Increment frame counter, set `cam->frame = frame`
3. Call the GPU kernel (`*_kernel()`) which enqueues the OpenCL NDRange
4. Call `accu_kernel()` which runs `draw_accu.cl` to convert the accumulation
   buffer to pixel colors and reads back to the mlx image buffer

The accumulation buffer allows progressive rendering: each frame adds one
sample per pixel, and the accumulation buffer is divided by the frame count to
get the averaged result.

### 3.2. Wireframe (Mode 0)

`wireframe_render.c` — pure CPU rasterization using minilibx:
- Projects 3D points to screen space
- Draws BVH cuboid boxes (rasterize_bvh, rasterize_cuboid)
- Draws object outlines (sphere outline, triangle outline, plane outline)
- Draws light positions as circles (rasterize_light_outline)
- Rainbow color palette for depth-based coloring (float_to_rainbow)
- BVH debug mode overlays the BVH structure on top of ray-traced views

---

## 4. OpenCL Pipeline

### 4.1. Initialization (src/opencl.c)

1. `init_opencl()` — enumerate platforms, find GPU device, call `init_gpu()`
2. `build_program()` — create context, command queue, compile program from
   embedded kernel source string with flags:
   `-Ishader -cl-fast-relaxed-math -cl-mad-enable`
3. `create_kernels()` — create 6 kernel objects: monte_carlo, normal_debug,
   phong, draw_accu, pbr, heat
4. `init_gpu()` — allocate GPU buffers:
   - `bu.accu` — accumulation buffer (float3 × WIDTH × HEIGHT, read-write)
   - `bu.img` — output image buffer (int × WIDTH × HEIGHT, read-write)

### 4.2. Kernel Source Embedding

The kernel source is a C string literal that `#include`s all .cl files:

```c
#define KERNEL_SOURCE \
"#include \"phong.cl\"\n" \
"#include \"calc_rays.cl\"\n" \
"#include \"draw_accu.cl\"\n" \
"#include \"intersect.cl\"\n" \
"#include \"phong_shading.cl\"\n" \
"#include \"sample_texture.cl\"\n" \
"#include \"pbr.cl\"\n" \
"#include \"sample_materials.cl\"\n" \
"#include \"random.cl\"\n" \
"#include \"monte_carlo.cl\"\n" \
"#include \"heat.cl\"\n" \
"#include \"normal_debug.cl\"\n"
```

### 4.3. Kernel Dispatch

Each `*_kernel.c` file:
1. Sets kernel arguments (camera, sphere/triangle/plane BVH buffers, textures,
   materials, lights, ambient, skybox)
2. Enqueues `clEnqueueNDRangeKernel` with global_size = {width, height}
3. Reads back the accumulation buffer to host

The `accu_kernel.c` runs the `draw_accu` kernel which divides the accumulated
float3 values by the frame count, converts to 0-255 range, and writes to the
integer image buffer for minilibx display.

### 4.4. BVH Upload (src/calc/bvh/load_bvh.c)

`load_bvh(mode, scene, state)`:
- mode 0: build sphere BVH (hierarchical sphere merging)
- mode 1: build SAH-based AABB BVH
- Uploads BVH2 arrays to GPU via `clCreateBuffer(CL_MEM_COPY_HOST_PTR)`

---

## 5. Mathematical Formulas (from shader code)

### 5.1. Camera Ray Generation (calc_rays.cl)

**Viewport setup (camera_utils.c):**
- `viewport_height = 2 * tan(fov * π / 180 / 2)`
- `viewport_width = viewport_height * (width / height)`
- Pixel delta: `pixel_delta_u = camera_right * viewport_width / width`

**Ray generation with DOF (calc_rays.cl):**
- Jitter: `jx = random() - 0.5, jy = random() - 0.5`
- `pixel_center = pixel00_loc + pixel_delta_u * (x + jx) + pixel_delta_v * (y + jy)`
- `ray.dir = normalize(pixel_center - cam.pos)`
- Focal point: `focal_point = cam.pos + ray.dir * focus_dist`
- Lens sampling: `disk = random_in_unit_disk() * lens_radius`
  - `r = sqrt(random())`, `θ = 2π * random()`
  - `disk = (r*cos(θ), r*sin(θ))`
- `ray.origin = cam.pos + camera_right * disk.x + camera_up * disk.y`
- `ray.dir = normalize(focal_point - ray.origin)`

### 5.2. Sphere Intersection (intersect.cl)

Quadratic formula:
- `oc = ray.origin - sphere.pos`
- `b = 2 * dot(ray.dir, oc)`
- `c = dot(oc, oc) - (diameter/2)²`
- `discriminant = b² - 4c`
- `t = (-b - sqrt(discriminant)) / 2` (nearest root)

### 5.3. Plane Intersection (intersect.cl)

- `denom = dot(ray.dir, plane.normal)`
- `t = dot(plane.pos - ray.origin, plane.normal) / denom`

### 5.4. Triangle Intersection (Möller–Trumbore, intersect.cl)

- `h = cross(ray.dir, edge_p2p0)`
- `f = 1 / dot(edge_p1p0, h)`
- `s = ray.origin - p0`
- `u = f * dot(s, h)`
- `q = cross(s, edge_p1p0)`
- `v = f * dot(ray.dir, q)`
- `t = f * dot(edge_p2p0, q)`

Barycentric coordinates (fill_uv_normal.cl):
- `bary.y = (d11*d20 - d01*d21) / denom`
- `bary.z = (d00*d21 - d01*d20) / denom`
- `bary.x = 1 - bary.y - bary.z`
- Normal = `p0.norm * bary.x + p1.norm * bary.y + p2.norm * bary.z`

### 5.5. Phong Shading (phong_shading.cl)

**Ambient:** `color = ambient * kd`

**Diffuse (per light):**
- `L = normalize(light_pos - hit_point)`
- `diffuse = kd * light_color * max(0, dot(L, N))`

**Specular (per light):**
- `R = reflect(N, L) = 2*dot(L,N)*N - L`
- `V = normalize(camera_pos - hit_point)`
- `specular = ks * light_color * max(0, dot(R, V))^ns`

**Shadow ray:** `get_color_through()` casts a ray to the light and checks if
anything is blocking. If `dot(hit_point - light_pos)² > distance²`, the
shadow ray passes (no occlusion); otherwise the light is blocked.

**Emissive:** `color += ke`

**Final:** `color = clamp(color, 0, 1)`

### 5.6. PBR / Fresnel / Reflectivity (sample_materials.cl)

**F0 (Fresnel at 0° incidence):**
- `F0 = ((ior - 1) / (ior + 1))²`
- For metals: `F0 = mix(F0, ks, metalness)`

**Schlick Fresnel:**
- `cos_θ = |dot(ray_dir, normal)|`
- `F = F0 + (1 - F0) * (1 - cos_θ)⁵`

**Glossy factor:**
- `glossy = 1 - roughness²`
- `reflectivity = F * glossy` (clamped to [0,1])

### 5.7. Refraction (Snell's Law, sample_materials.cl)

`vec3_refract(ray_dir, normal, eta)` where `eta = n1/n2`:
- `cos_i = -dot(ray_dir, normal)`
- `cos_t² = 1 - eta² * (1 - cos_i²)`
- If `cos_t² < 0`: total internal reflection → reflect instead
- `cos_t = sqrt(cos_t²)`
- `refract_dir = ray_dir * eta + normal * (eta * cos_i - cos_t)`

### 5.8. PBR Bounce (pbr.cl)

The PBR kernel does up to `MAX_BOUNCE` (4) bounces:
1. Cast ray, hit scene
2. Sample materials (including normal maps, roughness, metalness)
3. `sample_refract()` decides reflection vs refraction based on opacity:
   - If `random > opacity`: refract (through transparent material)
   - Else: reflect
4. `accumulated_color += phong_shading(...) * (1 - reflectivity) * through_power`
5. `through_power *= reflectivity`
6. If skybox hit: `accumulated_color += skybox_color * through_power`, break

### 5.9. Monte Carlo Path Tracing (monte_carlo.cl + sample_materials.cl)

**GGX/Trowbridge-Reitz microfacet sampling (sample_ggx_gpu):**
- `a = roughness²` (alpha)
- `φ = 2π * u1` (azimuthal)
- `cos_θ = sqrt((1 - u2) / (1 + (a² - 1) * u2))` (polar)
- `sin_θ = sqrt(1 - cos_θ²)`
- Half vector: `H = (cos(φ)*sin_θ, sin(φ)*sin_θ, cos_θ)`
- Transform to tangent space: `H = T*h.x + B*h.y + N*h.z`

**Path tracing loop (monte_carlo.cl):**
- `through_power = (0.33, 0.33, 0.33)` (initial — note: 3× scaling later)
- Up to `MAX_BOUNCE` (4) bounces
- `path_sample_materials()`:
  - If `random > opacity`: refract with GGX-sampled direction
    - On first refraction (is_diffract): `through_power *= rainbow_color() * 3`
    - Dispersion: `get_ni_by_color(ni, through_power, 0.03)` — modulates IOR
      based on the path's "color" (wavelength) for chromatic dispersion
  - Else: reflect with GGX-sampled direction
- If emissive hit: `accumulated += ke * through_power`, return
- `accumulated += kd * (1 - reflectivity) * through_power`
- `through_power *= reflectivity`
- Skybox: `img[pixel] += skybox * accumulated * 3` (3× boost)

**Chromatic dispersion (get_ni_by_color):**
- Converts RGB to hue (0-240°, excluding magenta)
- Maps hue to spectrum index (0-255)
- `wavelength_factor = (spectrum_index / 127.5) - 1`
- `ni = ni_base + wavelength_factor * dispersion * (ni_base - 1)`

**Rainbow color (for dispersion):**
- Random color from red → orange → green → blue → violet palette

### 5.10. Normal Debug (normal_debug.cl)

- `img[pixel] = normal * 0.5 + 0.5` (maps [-1,1] to [0,1])

### 5.11. Heat Map (heat.cl)

- Counts BVH node intersections per ray (`hit_bvh_depth`)
- 10 color palettes (2-4 gradient stops each)
- `heatmap(value, palette_idx)` — linear interpolation between palette stops
- `value = hit_depth / (max_depth²)` (normalized)

### 5.12. Accumulation (draw_accu.cl)

- `avg = accu[pixel] / sample_count * 255`
- `avg = clamp(avg, 0, 255)`
- Convert to packed RGB int for minilibx

---

## 6. BVH Construction

### 6.1. Two BVH Types

1. **Sphere BVH** (mode 0): Hierarchical merging of sphere bounding spheres.
   Each node has a position and size. Merging picks the two nearest spheres
   by combined area and merges them. Used for spheres only.

2. **AABB BVH with SAH** (mode 1): Surface Area Heuristic-based construction.
   Uses binning (16 bins per axis) to find optimal split. Used for triangles
   (OBJ meshes). Also builds a sphere AABB BVH.

### 6.2. SAH Algorithm (bvh_sah.h + sah/)

Constants:
- `NUM_BINS = 16` — bins per axis
- `LEAF_SIZE = 1` — max objects per leaf
- `CT = 1.0` — traversal cost
- `CI = 2.0` — intersection cost
- `SM = 1e30` — sentinel for infinity

SAH cost function:
- For each split candidate, compute:
  - `cost = CT + CI * (SA_left * N_left + SA_right * N_right) / SA_parent`
- Choose the split with minimum cost
- If best cost > leaf cost: make leaf

### 6.3. BVH2/4/8 Conversion (bvh_ary/)

- `bvh4.c`: Packs BVH2 nodes into BVH4 (4 children per node)
- `bvh8.c`: Packs BVH2 nodes into BVH8 (8 children per node)
- BVH2 uses linear traversal with `skip` pointers (stackless)
- BVH4/BVH8 use stack-based traversal with `WIDE_BVH_STACK_SIZE = 64`

### 6.4. GPU Traversal (intersect.cl)

BVH2: Stackless linear traversal using `skip` pointers:
```
node = 0
while node != -1:
    if hit_box(ray, bvh[node]):
        if leaf: test intersection
        else: node++
    else: node = bvh[node].skip
```

BVH4/BVH8: Stack-based traversal:
```
stack[0] = 0; sp = 1
while sp > 0:
    node = stack[--sp]
    if hit_box(ray, bvh[node]):
        if leaf: test children (negative indices = leaf references)
        else: push all children
```

Negative child indices in BVH4/8 encode leaf references: `leaf = -1 - child`

---

## 7. Scene Parsing

### 7.1. .rt File Format

Lines starting with `#` are comments. Keywords:

| Keyword | Syntax | Description |
|---------|--------|-------------|
| `C` | `C posX,Y,Z rotX,Y,Z FOV` | Camera |
| `A` | `A intensity R,G,B` | Ambient light |
| `L` | `L posX,Y,Z brightness R,G,B` | Point light |
| `sp` | `sp posX,Y,Z diameter material_name` | Sphere |
| `pl` | `pl posX,Y,Z normX,Y,Z R,G,B material_name scaling` | Plane |
| `obj` | `obj path.obj posX,Y,Z dirX,Y,Z scaleX,Y,Z` | OBJ mesh |
| `mtl` | `mtl path.mtl` | Load MTL file |
| `sky` | `sky path.ppm` | Skybox texture |

### 7.2. MTL File Format (standard Wavefront .mtl + extensions)

| Keyword | Description |
|----------|-------------|
| `newmtl name` | New material definition |
| `Ns value` | Shininess (specular exponent) |
| `Ka r g b` | Ambient color |
| `Kd r g b` | Diffuse color |
| `Ks r g b` | Specular color |
| `Ke r g b` | Emissive color (extension) |
| `Ni value` | Index of refraction |
| `d value` | Opacity (1=opaque, 0=transparent) |
| `Pr value` | Roughness (extension, 0=mirror, 1=fully rough) |
| `Pm value` | Metalness (extension, 0=dielectric, 1=metal) |
| `map_Kd path` | Diffuse texture map |
| `map_bump path` | Normal/bump map |
| `map_Pr path` | Roughness map |
| `map_Ka path` | Ambient occlusion map |
| `map_d path` | Opacity map |
| `map_Pm path` | Metalness map |

### 7.3. OBJ File Format (Wavefront .obj)

Parsed elements:
- `v x y z` — vertex position
- `vn x y z` — vertex normal
- `vt u v` — texture coordinate
- `f v/vt/vn ...` — face (triangulated)
- `mtllib path.mtl` — material library
- `usemtl name` — apply material to subsequent faces
- `o name` — object name

Faces are converted to triangles with precomputed edge vectors and dot
products for Möller-Trumbore intersection.

---

## 8. Build System

### 8.1. Submodule Dependency Chain

```
minilibx-linux (MLX)
    ↑
libft (LIBFT)
    ↑
mlx_wrapper (MLXW) — depends on MLX + LIBFT
    ↑
font_renderer (FONT_RENDER) — depends on MLXW + MLX + LIBFT
    ↑
mlxui (MLXUI) — depends on FONT_RENDER + MLXW + MLX + LIBFT
    ↑
xcerrcal — error handling (independent)
```

The Makefile builds these in order: MLX → LIBFT → MLXW → FONT_RENDER → MLXUI
→ XCERRCAL, then links all archives into the final binary.

### 8.2. Build Targets

| Target | Description |
|--------|-------------|
| `all` | Default build |
| `fast` | Optimized build (-Ofast -march=native -mtune=native -msse3) |
| `debug` | Debug build (-g3, DEBUG_LVL=1) |
| `inspect` | Inspection build (-g3, for LLDB/gdb) |
| `profile` | Profiling build (-g3 -pg, for gprof) |
| `san-mem` | AddressSanitizer (all overflow/UAF checks) |
| `san-leak` | LeakSanitizer (leak detection + ASan) |
| `san-ub` | UBSan (all undefined behavior checks) |
| `re` | fclean + all |
| `refast` | fclean + fast |
| `redebug` | fclean + debug |
| `reinspect` | fclean + inspect |
| `reprofile` | fclean + profile |
| `resan-mem` | fclean + san-mem |
| `resan-leak` | fclean + san-leak |
| `resan-ub` | fclean + san-ub |
| `clean` | Remove object files + dep files |
| `fclean` | clean + remove libraries + binary |
| `help` | Show available targets (currently minimal) |
| `print-%` | Print value of make variable % |
| `bonus` | Same as all |

### 8.3. Build Flags

| Flag | Default | Description |
|------|---------|-------------|
| `WIDTH` | 500 (or MAX_WIDTH if FULLSCREEN) | Window width |
| `HEIGHT` | 500 (or MAX_HEIGHT if FULLSCREEN) | Window height |
| `FULLSCREEN` | 0 | Use screen resolution |
| `RESIZEABLE` | 0 | Enable window resize |
| `WINDOWLESS` | 0 | Headless mode |
| `PERF` | 0 | Performance mode |
| `NPROC` | $(nproc) | Number of CPU cores |
| `VERBOSE` | 0 | Show compile commands |
| `CL_TARGET_OPENCL_VERSION` | 300 | OpenCL target version |
| `DEBUG_LVL` | 0 | Debug level (5=debug mode) |

### 8.4. Sanitizer Options (sanitize.mk)

ASAN_OPTIONS — extensive: intercept_tls, detect_leaks=0, quarantine=512MB,
redzone=128, report_globals, strict_init_order, container_overflow,
strict_string_checks, etc.

LSAN_OPTIONS — verbosity=1, use_registers, use_globals, use_stacks,
use_root_regions, use_tls, print_suppressions=false.

UBSAN_OPTIONS — print_stacktrace, halt_on_error=0, verbosity, report_error_type.

### 8.5. Machine-Specific Compilation

The Makefile detects the machine ID (`/etc/machine-id` hashed with sha256)
and switches between:
- **Home machine** (matching hash): Uses gcc-14, home ar/ranlib, disables XTEST
- **Other machines**: Uses gcc-12, llvm-ar-12, llvm-ranlib-12, enables XTEST

This is for the developers' specific machines.

### 8.6. OpenCL Build Flags

The OpenCL program is compiled with:
`-Ishader -cl-fast-relaxed-math -cl-mad-enable`

- `-cl-fast-relaxed-math`: Enables fast math optimizations
- `-cl-mad-enable`: Allow multiply-add instructions

---

## 9. Interactive Controls

### 9.1. Keyboard (loop_hook.c)

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Move left |
| D | Move right |
| Space | Move up |
| Shift | Move down |
| Q | Roll left |
| E | Roll right |
| 1 | Wireframe mode |
| 2 | Phong mode |
| 3 | PBR mode |
| 4 | Monte Carlo mode |
| - | Normal debug mode |
| = | Heat map mode |
| (mouse) | Yaw/pitch look |

### 9.2. Mouse (loop_hook.c)

- Mouse movement controls yaw (horizontal) and pitch (vertical)
- `SENSITIVITY = 0.001` — mouse sensitivity
- `ROLL_SENSITIVITY = 0.01` — roll speed
- `MAX_PITCH = 1.539` (~88°) — prevents flipping
- Movement speed: `MOVE_SPEED * (1 + ctrl) * delta_time` — ctrl doubles speed

### 9.3. BVH Debug

- `bvh_debug` flag toggles BVH visualization overlay
- `bvh_depth` controls which depth level to visualize (-1 = all)
- `bvh_color_offset` cycles through color palettes
- `bvh_mode` switches between sphere BVH (0) and AABB BVH (1)

---

## 10. Asset Catalog

### 10.1. Scenes (.rt files)

| File | Description |
|------|-------------|
| `asset/42.rt` | 42 subject scene — 500+ spheres with camera/light/ambient |
| `asset/scenes/template.rt` | Default scene with materials + OBJ objects |
| `asset/scenes/cornell.rt` | Cornell box scene with bunny |
| `asset/scenes/rgb.rt` | RGB test scene with glass spheres + skybox |
| `asset/scenes/chess.rt` | Chess room scene |
| `asset/scenes/marble.rt` | Marble/onyx/gold spheres |
| `asset/scenes/refract.rt` | Refraction test scene |

### 10.2. OBJ Meshes

| Path | Description |
|------|-------------|
| `asset/AMG/` | McLaren SLR 722 Edition (high-poly) |
| `asset/jesko/` | Koenigsegg Jesko (high-poly) |
| `asset/porsche/` | Porsche (high-poly) |
| `asset/bunny/` | Stanford Bunny (low/mid/high poly) |
| `asset/cornel/` | Cornell box + glass cube + demo |
| `asset/casino/` | Casino interior (high-poly) |
| `asset/chess/` | Chess set + room |
| `asset/difract/` | Refraction test object |
| `asset/half/` | Various primitives (cylinder, icosphere, monkey, prism) |
| `asset/square.obj` | Square plane |
| `asset/prism/` | Prism |

### 10.3. Textures

- PPM format (miniRT's primary texture format)
- PNG format (some assets)
- Skybox: `asset/texture/skybox/` (nebula, indoor)
- Material textures: `asset/texture/` with subdirectories per material type
  (checkerboard, fence, foil, gold, leather, marble, metal, onyx, paving,
  sand, tiles, wood)

### 10.4. Fonts

- `asset/fonts/JetBrainsMono-ExtraLight.ttf` — used by font_renderer for
  in-window text rendering (FPS counter, etc.) — currently commented out

---

## 11. Error Handling (rt_xcerrcal.h)

The project uses the `xcerrcal` library for structured error handling:

```c
typedef enum e_rt_err {
    RT_E_ARGC, RT_E_GRAPHICS, RT_E_PARSING, RT_E_ARGS,
    RT_E_AMBIENT, RT_E_CAMERA, RT_E_LIGHT, RT_E_OBJ,
    RT_E_PLANE, RT_E_SKY, RT_E_SPHERE, RT_E_TEX,
    RT_E_OBJ_FAIL, RT_E_OBJ_NO_MAT, RT_E_NO_TEX, RT_E_NO_PARSER,
    RT_E_UNKNOW_MAT, RT_E_UNKNOW_TEX, RT_E_UNKNOW_NMAP,
    RT_E_UNKNOW_ROUGHNESS, RT_E_UNKNOW_AMBIENT, RT_E_UNKNOW_OPACITY,
    RT_E_FB_DOUBLE, RT_E_FB_NO, RT_E_VERTEX, RT_E_NORMAL,
    RT_E_UV, RT_E_FACE, RT_E_UNDEFINED_TYPE, RT_E_KERNEL,
    RT_ERRS_NUM
} t_rt_err;
```

Each error has a message template (`RT_E_MSG_*`) with format specifiers.
Errors are registered at startup and printed at exit via `print_errs()`.

---

## 12. Export Features

### 12.1. PPM Export (export_to_ppm.c)

Exports the current render to a PPM file.

### 12.2. Scene Export (export_scene/)

`export_scene.c` + `write_*.c` — exports the current scene back to .rt format:
- `write_base.c` — camera + ambient
- `write_lights.c` — point lights
- `write_materials.c` — material definitions
- `write_objects.c` — OBJ mesh references
- `write_primitives.c` — spheres + planes

---

## 13. Notable Design Decisions

1. **Dual BVH systems**: The project implements both a sphere-based BVH
   (hierarchical sphere merging) and an AABB-based BVH with SAH. The user
   can switch between them at runtime.

2. **BVH2/4/8 branching**: The BVH is built as BVH2 first, then can be
   packed into BVH4 or BVH8 for wider GPU traversal. BVH2 uses stackless
   traversal (skip pointers); BVH4/8 use stack-based traversal.

3. **OpenCL kernel embedding**: All .cl files are `#include`d into a single
   C string literal and compiled as one program. This avoids file I/O at
   runtime but means the kernel source is compiled into the binary.

4. **Progressive accumulation**: The render loop accumulates samples over
   multiple frames. When the camera moves or render mode changes, the
   accumulation buffer is cleared and restarts. The `draw_accu` kernel divides
   by frame count to get the averaged result.

5. **Chromatic dispersion in Monte Carlo**: The path tracer implements
   wavelength-dependent refraction by converting the accumulated
   `through_power` RGB to a hue, mapping it to a spectrum index, and
   modulating the IOR. This creates rainbow-like dispersion effects in
   transparent materials.

6. **GGX microfacet sampling**: Both PBR and Monte Carlo modes use importance
   sampling of the GGX/Trowbridge-Reitz distribution for physically plausible
   rough specular reflections.

7. **Normal map tangent space**: The project builds a TBN (tangent-bitangent-
   normal) frame per hit to transform normal map samples from tangent space
   to world space. The tangent is derived from the geometric normal using a
   branchless up-vector selection.

8. **Machine-specific compiler selection**: The Makefile hashes
   `/etc/machine-id` and switches between gcc-14 (home) and gcc-12/llvm-ar
   (other machines), with different warning flags for each.

9. **42 Norm compliance**: The code follows the 42 School coding norm
   (snake_case functions, specific header format, etc.) while implementing
   features far beyond the original subject scope.

10. **Dual render architecture**: CPU rasterization (wireframe/debug) and
    GPU ray tracing (all other modes) coexist. The CPU mode doesn't need
    OpenCL or BVH; GPU modes build the BVH lazily on first non-wireframe
    frame.
