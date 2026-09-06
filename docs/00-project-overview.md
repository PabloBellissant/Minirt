# miniRT — Project Overview

## What is miniRT?

miniRT is a **GPU-accelerated ray tracer** written in C with OpenCL. It started as the final graphics project of the **42 School** curriculum — a minimalist ray tracer rendering spheres, planes, and cylinders with Phong shading — but has evolved far beyond the original specification into something closer to a **miniature Blender**: a fully interactive 3D scene editor with real-time rendering, a complete UI system, mesh loading, PBR materials, Monte Carlo path tracing, and a production-grade acceleration structure.

## Original 42 Subject

The original 42 miniRT subject required:

- **C language only**, with the **minilibx** (MLX42) graphics library
- Parse a `.rt` scene file with: ambient (`A`), camera (`C`), light (`L`), sphere (`sp`), plane (`pl`), cylinder (`cy`)
- **Phong reflection model** for shading
- Flat or smooth colors — no textures
- A single, fixed render mode
- Basic keyboard controls for camera movement
- No BVH or any acceleration structure — naive O(n) intersection tests

## How Far We Went

The current miniRT implements a full production-grade ray tracer that far exceeds the original subject. Honestly, we went a bit too far down the rabbit hole — we almost built a Blender clone. For a school project with two people in 8 months, using an obscure graphics library (minilibx) and under a strict coding norm (norminette), it's still pretty great. But it comes with real trade-offs.

### The Honest Truth

- **The norminette is disabling at this scale.** The 42 coding norm (max 25 lines per function, no `for` loops, specific formatting) is excellent for learning discipline, but at 251 source files it becomes a real hindrance.
- **The base graphics library is a problem.** minilibx is a barebones X11 wrapper with no hardware-accelerated 2D. Every UI element — TTF font rendering, panels, sliders, color pickers — is CPU-drawn pixel by pixel. This destroys performance.
- **Portability issues.** We developed on 42 campus iMacs with self-compiled, somewhat wanky OpenCL packages. The build system literally has machine-ID detection to switch compilers.
- **Obscure C paradigms.** We used abusive patterns to mimic OOP in C (notably in `mlxui` for polymorphism and `mlx_wrapper` for hooks). This may not compile on all compiler versions.
- **A lot was designed but never implemented.** Infrastructure exists for features that were scrapped to keep things manageable.

### What Was Actually Built

### Core Rendering

- **OpenCL GPU rendering** — all shading, intersection, and accumulation runs on the GPU via OpenCL compute kernels
- **6 render modes**: wireframe (CPU rasterized), Phong, PBR, Monte Carlo path tracing, normal debug, heat map
- **PBR (Physically Based Rendering)** with Fresnel (Schlick approximation) and **GGX microfacet distribution** for realistic specular
- **Monte Carlo path tracing** with progressive accumulation, multi-bounce indirect illumination, and **chromatic dispersion** (wavelength-dependent refraction)
- **Camera**: position, rotation, field of view, **depth of field** (lens radius + focus distance), auto exposure
- **Exposure control** with real-time adjustment in the UI
- **Progressive accumulation** — samples accumulate over frames for noise-free Monte Carlo results

### Scene Objects

- **Sphere** (`sp`) — position, diameter, material
- **Plane** (`pl`) — position, normal, material, texture scaling
- **Cylinder** (`cy`) — position, rotation, diameter, height, material (WIP render with full parser support)
- **Mesh** (`obj`) — Wavefront OBJ loading with full transform (position, rotation, scale), per-vertex normals, UV coordinates, and material assignment
- **Skybox** (`sky`) — equirectangular environment map via PPM texture
- **Point lights** (`L`) — position, brightness, color

### Materials (MTL)

- Full MTL file parser supporting: `newmtl`, `Ns` (specular exponent), `Ka` (ambient), `Kd` (diffuse), `Ks` (specular), `Ke` (emissive), `Ni` (index of refraction), `d` (opacity), `Pr` (roughness), `Pm` (metalness)
- **Texture maps**: `map_Kd` (albedo), `map_bump` (normal map), `map_Pr` (roughness map), `map_Ka` (ambient occlusion), `map_d` (opacity map), `map_Pm` (metalness map)
- 8+ materials included in the minirt-assets repository

### BVH Acceleration

- **Unified BVH system** with three bounding shapes:
  - **AABB** (Axis-Aligned Bounding Box) — fast, simple
  - **Sphere** — optimal for sphere-heavy scenes
  - **OBB** (Oriented Bounding Box) — PCA-driven, computed via Jacobi eigenvalue decomposition + quaternion rotation, tightest fit
- **Three splitting algorithms**:
  - **SAH** (Surface Area Heuristic) — bins-based, minimizes expected traversal cost
  - **Median Primitive** — splits primitives at the median
  - **Median Space** — splits bounding volume at the spatial median
- **BVH_ARITY=2** (binary tree)
- GPU-side traversal with `hit_aabb`, `hit_obb`, `hit_sphere` functions
- OBB uses quaternion-based ray-box intersection (avoids full matrix inverse)
- Debug visualization (wireframe BVH overlay, heat map by depth)

### User Interface

- **Full UI system** built on `mlxui` — a custom GUI toolkit over minilibx
- **Left panel** with: scene list (hierarchical object browser), edit panels, render mode switch
- **Object selection** — click-to-select in viewport, first-selected highlight
- **Edit panels** per object type: geometry transforms (position, rotation, scale), material properties (Ns, Kd, Ks, Ni, d, Pr, Pm, emissive), color pickers, sliders, texture selectors
- **Camera parameters**: FOV, lens radius, focus distance
- **Render controls**: mode switching, BVH debug toggle, export render task
- **FPS counter** and info display overlay
- **Export to PPM** and **scene export** (.rt format)

### Build and Development

- **251 C source files**, **30 header files**, **14 OpenCL kernel files**, **48 .mk makefiles**
- **7 library submodules**: `libft`, `minilibx-linux`, `mlx_wrapper`, `font_renderer`, `mlxui`, `xcerrcal`
- **1 asset submodule**: `minirt-assets` — test scenes, meshes, materials, textures (PPM format)
- **Modular build system** using `mkidir` with automatic dependency tracking
- **Sanitizer support**: AddressSanitizer, LeakSanitizer, UndefinedBehaviorSanitizer
- **3 debug levels**: DEBUG_LVL 1–5 controls verbosity per submodule
- **Machine-ID based compiler selection** for local vs. remote development
- **Tiered error handling** via `xcerrcal` library

## Feature Comparison

| Feature | 42 Subject | miniRT |
|---|---|---|
| Render backend | CPU | **GPU (OpenCL)** |
| Shading | Phong | **Phong, PBR (Fresnel/GGX), Monte Carlo** |
| Render modes | 1 | **6** (wireframe, Phong, PBR, Monte Carlo, normal, heat) |
| Acceleration | None | **BVH** (AABB/Sphere/OBB + SAH/median) |
| Primitives | Sphere, Plane, Cylinder | Sphere, Plane, **Cylinder (WIP)**, **Mesh (OBJ)** |
| Materials | Color only | **Full MTL** with texture maps |
| Textures | None | **map_Kd, map_bump, map_Pr, map_Ka, map_d, map_Pm** |
| Skybox | None | **Environment map** via PPM |
| Camera | Fixed | **DOF**, exposure, focus distance |
| UI | None | **Full UI**: scene list, edit panels, selection, color pickers |
| Progressive | None | **Accumulation buffer** for Monte Carlo |
| Dispersion | None | **Chromatic dispersion** |
| OBJ loading | None | **Full OBJ** with v/vn/vt, usemtl, mtllib |
| Error handling | Basic | **Structured** via xcerrcal library |
| File count | ~5 | **251 .c, 30 .h, 14 .cl** |

## minirt-assets Repository

The [minirt-assets](https://github.com/ketodin/minirt-assets) repository provides:

- **Test scenes** (`.rt` files): Cornell box, refraction test, marble, chess, RGB, template
- **Meshes** (`.obj`): glass cube, monkey head, diffraction grating, chess set, bunny, BMW, Porsche, Jesko, AMG, casino, dragon, triangle, square
- **Materials** (`.mtl`): sand, gold, leather, tiles, foil, marble, onyx, wood, metal, fence, paving, ornament, checkerboard
- **Textures** (`.ppm`): skyboxes (nebula, studio), procedural textures, normal maps, roughness maps, ambient occlusion maps

---

## Scrapped Features

If we could redo it from scratch, a lot would change. Here's what was
designed but never finished:

- **BVH UI panel** — A full UI section for generating on-the-fly BVH types
  (picking shapes, splitting algorithms, and arity from the interface).
  Scraped to keep the BVH system simpler.
- **Multiple BVH arities** — BVH4 and BVH8 (quad and octree branching) were
  designed and partially implemented. Removed in favor of a single binary
  tree (BVH_ARITY=2).
- **DOP shapes** — Discrete Oriented Polytopes (DOP-4, DOP-6, DOP-8) were
  planned as additional bounding shapes alongside AABB, Sphere, and OBB.
  Never implemented.
- **Split/merge algorithms** — Additional algorithms for determining optimal
  splits and merges of bounding volumes. Only SAH, median-primitive, and
  median-space made it in.
- **Full object editing** — Per-vertex mesh editing, material assignment UI,
  transform gizmos. Only basic property editing is available.
- **Full scene hierarchy** — A complete scene hierarchy tree like Blender's
  outliner. A simplified scene list exists instead.
- **World panel** — A world settings panel for changing global settings like
  ambient light.
- **Dissociated camera/player movement** — Like Blender's separate camera
  object vs. viewport navigation. Never implemented.
- **PNG parser** — A PNG texture parser was planned. Only PPM/PFM is supported.
- **Grid world, anchor rotation, movement arrows** — Grid floor display,
  rotation around a world anchor, and position/rotation movement arrows on
  selected objects (like Blender gizmos). All planned, none implemented.