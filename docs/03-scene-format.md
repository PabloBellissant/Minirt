# miniRT - Scene Format (.rt)

## Overview

miniRT scene files use the `.rt` extension. They are plain-text files with one directive per line. Lines starting with `#` or `//` are comments. Values are comma- or whitespace-separated. The parser uses `ft_scan()` - a typed scanf with range validation - defined in the format macros below.

```rt
# Ambient light
A 0.2 255,255,255

# Camera
C 0,5,-10 0.5,-0.7,0 70

# Light
L 0,10,0 1 255,255,255

# Sphere with material
mtl asset/materials/gold.mtl
sp 3,2,0 2 0,0,0 gold

# Plane
pl 0,-1,0 0,1,0 0,0,0 checkerboard 1
```

## Identifiers

| Identifier | Type | Description |
|---|---|---|
| `A` | Ambient | Global ambient light |
| `C` | Camera | Viewpoint and projection |
| `L` | Light | Point light source |
| `sp` | Sphere | Sphere primitive |
| `pl` | Plane | Infinite plane primitive |
| `cy` | Cylinder | Finite cylinder |
| `obj` | Mesh | Wavefront OBJ mesh file |
| `sky` | Skybox | Equirectangular environment map |
| `mtl` | Material | MTL material library file |

### Ambient - `A`

```
A  ratio  R,G,B
```

| Field | Type | Range | Description |
|---|---|---|---|
| `ratio` | float | `[0, 1]` | Ambient intensity multiplier |
| `R,G,B` | int | `[0, 255]` | Ambient color (RGB) |

The final ambient color is computed as $\text{ratio} \times (R/255, G/255, B/255)$.

**Example:**
```
A 0.2 255,255,255
```

### Camera - `C`

```
C  x,y,z  rx,ry,rz  fov
```

| Field | Type | Range | Description |
|---|---|---|---|
| `x,y,z` | float | unlimited | Camera position in world space |
| `rx,ry,rz` | float | `[-1, 1]` | Normalized rotation vector (multiplied by pi internally) |
| `fov` | int | `[0, 180]` | Vertical field of view in degrees |

The rotation vector is normalized and scaled by pi to produce Euler-like orientation angles. The camera also has **depth of field** parameters (`lens_radius = 0.001f`, `focus_dist = 1`) that can be adjusted via the UI edit panel.

**Example:**
```
C 0,0,0 0.5,-0.7,0 70
```

### Light - `L`

```
L  x,y,z  brightness  R,G,B
```

| Field | Type | Range | Description |
|---|---|---|---|
| `x,y,z` | float | unlimited | Light position |
| `brightness` | float | `[0, 1]` | Brightness multiplier |
| `R,G,B` | int | `[0, 255]` | Light color |

The final light color is $\text{brightness} \times (R/255, G/255, B/255)$.

**Example:**
```
L 0,10,0 1 255,255,255
L -5,10,0 1 0,0,255
```

### Sphere - `sp`

```
sp  x,y,z  diameter  R,G,B  [mat_name]
```

| Field | Type | Range | Description |
|---|---|---|---|
| `x,y,z` | float | unlimited | Center position |
| `diameter` | float | unlimited | Sphere diameter ($\text{radius} = \text{diameter} / 2$) |
| `R,G,B` | int | `[0, 255]` | Diffuse color (used if no material name given) |
| `mat_name` | string | - | Optional material name (must be loaded via `mtl` first) |

**Examples:**
```
sp 0,3,0 3 255,255,255
sp -5,4.5,0 8 0,0,0 emissive_red
sp 0,8.5,0 5 0,0,0 sand
```

### Plane - `pl`

```
pl  x,y,z  nx,ny,nz  R,G,B  [mat_name]  [texture_scaling]
```

| Field | Type | Range | Description |
|---|---|---|---|
| `x,y,z` | float | unlimited | Point on the plane |
| `nx,ny,nz` | float | `[-1, 1]` | Normalized normal vector |
| `R,G,B` | int | `[0, 255]` | Diffuse color |
| `mat_name` | string | - | Optional material name |
| `texture_scaling` | float | unlimited | Texture coordinate scaling factor (default 1.0) |

Tangent and bitangent vectors are automatically computed from the normal for normal mapping.

**Examples:**
```
pl 0,0,0 0,1,0 0,0,0 checkerboard 1
pl -5,0,0 1,0,0 0,0,0 gold 0.1
```

### Cylinder - `cy`

```
cy  x,y,z  rx,ry,rz  diameter  height  R,G,B  [mat_name]
```

| Field | Type | Range | Description |
|---|---|---|---|
| `x,y,z` | float | unlimited | Base center position |
| `rx,ry,rz` | float | `[-1, 1]` | Normalized axis direction |
| `diameter` | float | unlimited | Cylinder diameter |
| `height` | float | unlimited | Cylinder height |
| `R,G,B` | int | `[0, 255]` | Diffuse color |
| `mat_name` | string | - | Optional material name |

**Example:**
```
cy 0,0,0 0,1,0 2 5 255,0,0
```

### Mesh (OBJ) - `obj`

```
obj  path  pos_x,pos_y,pos_z  rot_x,rot_y,rot_z  scale_x,scale_y,scale_z
```

| Field | Type | Range | Description |
|---|---|---|---|
| `path` | string | - | Path to `.obj` file (relative to `miniRT/` or absolute) |
| `pos_x,y,z` | float | unlimited | Translation |
| `rot_x,y,z` | float | unlimited | Rotation in radians (applied to vertices and normals) |
| `scale_x,y,z` | float | unlimited | Scale factor per axis |

The OBJ file is parsed and all faces are converted to `t_triangle` objects with barycentric precomputation. The mesh is stored as a `t_mesh` entry with offset and triangle count.

**Example:**
```
obj asset/bunny/bunny_high_poly.obj 0,0,0 0,0,5 1,1,1
obj asset/porsche/porsche.obj 31,0,3 3,0,5 1,1,1
obj asset/difract/difract.obj 0,-1,0 0,0,5 1,1,1
```

### Skybox - `sky`

```
sky  path
```

| Field | Type | Description |
|---|---|---|
| `path` | string | Path to a PPM image file (equirectangular projection) |

Loads an environment map that is sampled by the GPU when rays miss all scene objects.

**Example:**
```
sky asset/texture/skybox/nebula.ppm
```

### Material Library - `mtl`

```
mtl  path
```

| Field | Type | Description |
|---|---|---|
| `path` | string | Path to a `.mtl` file |

Loads a Wavefront MTL file. All materials defined in the file become available for use by scene objects. The path is recorded in `scene.mtl_list`.

**Example:**
```
mtl asset/materials/sand.mtl
mtl asset/materials/gold.mtl
```

## MTL Format

MTL files follow the Wavefront OBJ material specification with miniRT-specific extensions. All values are parsed via `ft_scan()` with the exact formats below.

### Supported Keywords

| Keyword | Format String | Description |
|---|---|---|
| `newmtl` | `" *newmtl  *%s *\\n"` | Start new material with given name |
| `Ns` | `" *Ns  *%f *\\n"` | Specular exponent (clamped to ≥ 50.0) |
| `Ka` | `" *Ka  *%f[1]  *%f[1]  *%f[1] *\\n"` | Ambient color (float RGB, `[0,1]`) - creates a gray-level ambient texture |
| `Kd` | `" *Kd  *%f[1]  *%f[1]  *%f[1] *\\n"` | Diffuse color (float RGB, `[0,1]`) - stored in BGR order on GPU, creates a color texture |
| `Ks` | `" *Ks  *%f[1]  *%f[1]  *%f[1] *\\n"` | Specular color (float RGB, `[0,1]`) |
| `Ke` | `" *Ke  *%f[1000]  *%f[1000]  *%f[1000] *\\n"` | Emissive color (float RGB, `[0,1000]`) - allows HDR emission |
| `Ni` | `" *Ni  *%f[0,5] *\\n"` | Index of refraction (`[0, 5]`) |
| `d` | `" *d  *%f[1] *\\n"` | Opacity (`[0, 1]`, 1 = opaque) - creates a gray-level opacity texture |
| `Pr` | `" *Pr  *%f[1] *\\n"` | Roughness (`[0, 1]`, 0 = smooth) - creates a gray-level roughness texture |
| `Pm` | `" *Pm  *%f[1] *\\n"` | Metalness (`[0, 1]`, 1 = metallic) - creates a gray-level metalness texture |
| `map_Kd` | `" *map_Kd  *%s *\\n"` | Diffuse/albedo texture map (PPM path); scaled by `Kd` values |
| `map_bump` | `" *map_bump  *%s *\\n"` | Normal/bump map (PPM path) |
| `map_Pr` | `" *map_Pr  *%s *\\n"` | Roughness texture map (PPM path); scaled by `Pr` value |
| `map_Ka` | `" *map_Ka  *%s *\\n"` | Ambient occlusion texture map (PPM path); scaled by `Ka` value |
| `map_d` | `" *map_d  *%s *\\n"` | Opacity texture map (PPM path) |
| `map_Pm` | `" *map_Pm  *%s *\\n"` | Metalness texture map (PPM path); scaled by `Pm` value |

### Material Struct (GPU-Side)

The `t_mat` struct definition and GPU-side material sampling are documented in [08-materials-and-textures.md](08-materials-and-textures.md), which covers the full struct, PBR properties, and texture map sampling.

### MTL Example

```mtl
# MiniRT MTL File

newmtl sand
Ns 10.0
Ka 1.000 1.000 1.000
Kd 1.000 1.000 1.000
Ks 0.040 0.040 0.040
Pm 0.0
Pr 1
Ni 1.5
map_Kd asset/texture/sand/texture.ppm
map_bump asset/texture/sand/normal.ppm
map_Pr asset/texture/sand/roughness.ppm
map_Ka asset/texture/sand/ambient.ppm
```

```mtl
newmtl checkerboard
Ns 800.0
Ka 0.8 0.8 0.8
Kd 1.0 1.0 1.0
Ks 0.3 0.3 0.3
Ni 1.0
d 1.0
Pr 0.25
Pm 1
map_Kd asset/texture/checkerboard/mat_preview_checkerboard.ppm
```

## OBJ Format

miniRT parses a subset of the Wavefront OBJ format. Supported keywords:

| Keyword | Parsed As | Description |
|---|---|---|
| `v` | `parse_vertex()` | Vertex position `x y z [w]` |
| `vn` | `parse_normal()` | Vertex normal `x y z` |
| `vt` | `parse_uv()` | Texture coordinate `u v [w]` |
| `f` | `parse_face()` | Face with format `v/vt/vn v/vt/vn v/vt/vn` (triangles only) |
| `usemtl` | `apply_mtl()` | Switch active material |
| `mtllib` | `parse_mtllib()` | Reference to external MTL file |

Face format (from parser):

```
f  v1/vt1/vn1  v2/vt2/vn2  v3/vt3/vn3
```

The face parser expects exactly 3 vertices (triangulated OBJ). Vertex, UV, and normal indices are 1-based (as per OBJ spec, automatically decremented to 0-based internally).

### OBJ Example

```obj
# MiniRT OBJ Mesh
mtllib checkerboard.mtl
usemtl checkerboard
v -1.0 0.0 1.0
v 1.0 0.0 1.0
v 1.0 0.0 -1.0
v -1.0 0.0 -1.0
vt 0.0 0.0
vt 1.0 0.0
vt 1.0 1.0
vt 0.0 1.0
vn 0.0 1.0 0.0
f 1/1/1 2/2/1 3/3/1
f 1/1/1 3/3/1 4/4/1
```

## Complete .rt Example

```rt
# Ambient
A 0.2 255,255,255

# Camera
C 0,5,-10 0.5,-0.7,0 70

# Lights
L 0,10,0 1 255,255,255
L -5,5,-5 0.5 200,200,255

# Material libraries
mtl asset/materials/sand.mtl
mtl asset/materials/gold.mtl
mtl asset/materials/checkerboard.mtl
mtl asset/materials/uni/emissive.mtl

# Primitives
sp 3,2,0 2 0,0,0 gold
sp -3,2,0 2 0,0,0 sand
pl 0,-1,0 0,1,0 0,0,0 checkerboard 1

# Mesh
obj asset/square.obj 0,3,-5 0,0,5 1,1,1

# Skybox
sky asset/texture/skybox/studio.ppm
```

## Parser Architecture

The scene is parsed in two phases:

1. **Phase 1 - `rt_parser()`**: Reads the `.rt` file line by line, dispatches to type-specific parsers (`sphere()`, `plane()`, `obj()`, etc.), populates `t_scene` with CPU-side data (objects vector, materials vector, textures vector, lights vector, mesh vector).

2. **Phase 2 - `fill_by_type()` → `fill_gpu_data()`**: Separates objects by type into GPU buffers (spheres, triangles, planes), creates BVH, uploads all buffers to the GPU via `clCreateBuffer` / `clEnqueueWriteBuffer`.

The OBJ and MTL parsers are recursive - `obj()` calls `parse_obj_file()` which calls `parse_obj_type()` → `parse_face()`/`parse_vertex()` etc., and `mtl()` calls `parse_mtl_file()` → `parse_mtl_type()` for each line. Both support nested file references via `mtllib` inside OBJ files.