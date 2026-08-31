# MiniRT — Scene Format Specification

This document defines the `.rt` scene file format, the `.mtl` material format,
and the `.obj` mesh format used by miniRT.

---

## 1. Overview

A miniRT scene is described in a plain-text `.rt` file. Lines beginning with
`#` are comments and are ignored. The file specifies the camera, lighting,
geometry, materials, and optional skybox.

The parser processes the file sequentially. Objects reference materials by name
and OBJ files reference meshes by path.

---

## 2. `.rt` File Keywords

### 2.1. Camera `C`

```
C posX,Y,Z rotX,Y,Z FOV
```

Defines the scene camera.

| Field | Type | Description |
|---|---|---|
| `posX,Y,Z` | float3 | Camera position in world space |
| `rotX,Y,Z` | float3 | Euler angles: pitch (X), yaw (Y), roll (Z) in degrees |
| `FOV` | int | Horizontal field of view in degrees |

There must be exactly one camera in the scene.

**Example:**
```
C 0,0,-5 0,0,0 60
```

### 2.2. Ambient Light `A`

```
A intensity R,G,B
```

Defines the ambient light color.

| Field | Type | Description |
|---|---|---|
| `intensity` | float | Ambient intensity multiplier (0.0 – 1.0) |
| `R,G,B` | float3 | Ambient color (0.0 – 1.0 per channel) |

There must be exactly one ambient light.

**Example:**
```
A 0.2 0.1,0.1,0.1
```

### 2.3. Point Light `L`

```
L posX,Y,Z brightness R,G,B
```

Defines a point light source.

| Field | Type | Description |
|---|---|---|
| `posX,Y,Z` | float3 | Light position in world space |
| `brightness` | float | Light intensity multiplier |
| `R,G,B` | float3 | Light color |

Multiple `L` lines may exist.

**Example:**
```
L 10,10,10 1.0 1.0,1.0,1.0
L -5,5,-5 0.5 0.8,0.6,1.0
```

### 2.4. Sphere `sp`

```
sp posX,Y,Z diameter material_name
```

Defines a sphere.

| Field | Type | Description |
|---|---|---|
| `posX,Y,Z` | float3 | Sphere center |
| `diameter` | float | Sphere diameter |
| `material_name` | string | Name of an existing MTL material |

**Example:**
```
sp 0,2,0 2 gold
sp -3,1,4 1.5 glass
```

### 2.5. Plane `pl`

```
pl posX,Y,Z normX,Y,Z R,G,B material_name scaling
```

Defines a plane (infinite).

| Field | Type | Description |
|---|---|---|
| `posX,Y,Z` | float3 | A point on the plane |
| `normX,Y,Z` | float3 | Plane normal direction |
| `R,G,B` | float3 | Base color (fallback if no diffuse texture) |
| `material_name` | string | Name of an existing MTL material |
| `scaling` | float | UV texture scaling factor |

The plane uses the `material_name` for its PBR properties; `R,G,B` acts as a
fallback diffuse color if no `map_Kd` is defined in the material.

**Example:**
```
pl 0,0,0 0,1,0 0.5,0.5,0.5 marble 1.0
```

### 2.6. OBJ Mesh `obj`

```
obj path.obj posX,Y,Z dirX,Y,Z scaleX,Y,Z
```

Loads and positions a Wavefront OBJ mesh.

| Field | Type | Description |
|---|---|---|
| `path.obj` | string | Path to the .obj file (relative to working directory or absolute) |
| `posX,Y,Z` | float3 | Translation in world space |
| `dirX,Y,Z` | float3 | Rotation in degrees (pitch, yaw, roll) |
| `scaleX,Y,Z` | float3 | Scale factors per axis |

All triangles from the OBJ file are placed into the scene's triangle array and
included in the BVH.

**Example:**
```
obj asset/bunny/bunny.obj 0,-1,3 0,45,0 0.5,0.5,0.5
```

### 2.7. MTL Reference `mtl`

```
mtl path.mtl
```

Loads a Wavefront MTL material library file. All materials defined in the file
become available for use by `sp`, `pl`, and OBJ meshes.

**Example:**
```
mtl asset/scenes/materials.mtl
```

### 2.8. Skybox `sky`

```
sky path.ppm
```

Sets a skybox texture. The texture is sampled when a ray does not intersect any
scene geometry.

| Field | Type | Description |
|---|---|---|
| `path.ppm` | string | Path to a PPM texture file (or PNG) |

**Example:**
```
sky asset/texture/skybox/nebula.ppm
```

---

## 3. Example `.rt` File

```rt
# Cornell box scene
A 0.3 0.2,0.2,0.2
C 0,0,5 0,0,0 60

# Materials
mtl asset/scenes/cornell.mtl

# Lights
L 0,3,0 0.8 1.0,1.0,1.0

# Objects
pl -2,0,0 1,0,0 1.0,0.0,0.0 red_wall 1.0
pl 2,0,0 -1,0,0 0.0,1.0,0.0 green_wall 1.0
pl 0,-1,0 0,1,0 0.8,0.8,0.8 white_floor 2.0
pl 0,3,0 0,-1,0 0.8,0.8,0.8 white_ceiling 1.0
pl 0,0,3 0,0,-1 0.8,0.8,0.8 white_back 1.0

sp 0.5,-0.5,1 1 gold
obj asset/bunny/bunny.obj -0.5,-0.5,0.5 0,0,0 0.3,0.3,0.3
```

---

## 4. MTL Material Format

MiniRT supports standard Wavefront MTL properties plus custom extensions for
PBR rendering.

### 4.1. Keyword Reference

| Keyword | Fields | Description |
|---|---|---|
| `newmtl name` | string | Begins a new material definition with the given name |
| `Ns value` | float | Shininess (Phong specular exponent). Higher = sharper highlights |
| `Ka r g b` | float3 | Ambient color. Multiplied with scene ambient in Phong mode. Also used as ambient occlusion map multiplier |
| `Kd r g b` | float3 | Diffuse color (albedo) |
| `Ks r g b` | float3 | Specular color. For metals, controls reflective tint |
| `Ke r g b` | float3 | **Emissive color (extension).** Emits light. Used as direct lighting in path tracing |
| `Ni value` | float | Index of refraction. Controls Fresnel and refraction (e.g., 1.0 = air, 1.33 = water, 1.5 = glass, 2.4 = diamond) |
| `d value` | float | Opacity (dissolve). 1.0 = fully opaque, 0.0 = fully transparent |
| `Pr value` | float | **Roughness (extension).** 0.0 = mirror smooth, 1.0 = fully rough. Squared to get alpha in GGX |
| `Pm value` | float | **Metalness (extension).** 0.0 = dielectric, 1.0 = metal. Blends F0 between dielectric and specular color |
| `map_Kd path` | string | Diffuse/albedo texture map |
| `map_bump path` | string | Normal or bump map. Used for surface detail perturbation |
| `map_Pr path` | string | Roughness texture map |
| `map_Ka path` | string | Ambient occlusion texture map |
| `map_d path` | string | Opacity texture map |
| `map_Pm path` | string | Metalness texture map |

### 4.2. Texture Maps

Texture maps are loaded from PPM or PNG files. They are sampled at the hit
point's UV coordinates using bilinear interpolation. If a texture map is not
provided, the corresponding scalar or color value from the material header
(`Kd`, `Pr`, `Pm`, etc.) is used as a fallback.

### 4.3. Example `.mtl` File

```mtl
newmtl gold
Ns 85.0
Ka 0.2 0.2 0.2
Kd 0.95 0.75 0.25
Ks 0.95 0.70 0.20
Ke 0.0 0.0 0.0
Ni 1.5
d 1.0
Pr 0.15
Pm 1.0
map_Kd asset/texture/gold/diffuse.ppm
map_bump asset/texture/gold/normal.ppm
map_Pr asset/texture/gold/roughness.ppm

newmtl glass
Ns 200.0
Ka 0.0 0.0 0.0
Kd 0.0 0.0 0.0
Ks 1.0 1.0 1.0
Ke 0.0 0.0 0.0
Ni 1.5
d 0.1
Pr 0.0
Pm 0.0

newmtl emissive_red
Ns 10.0
Ka 0.0 0.0 0.0
Kd 0.0 0.0 0.0
Ks 0.0 0.0 0.0
Ke 10.0 0.0 0.0
Ni 1.0
d 1.0
Pr 0.5
Pm 0.0
```

---

## 5. OBJ Mesh Format

MiniRT parses a subset of the Wavefront OBJ format. Faces are triangulated.

### 5.1. Supported Elements

| Token | Format | Description |
|---|---|---|
| `v` | `v x y z` | Vertex position (float3) |
| `vn` | `vn x y z` | Vertex normal (float3) |
| `vt` | `vt u v` | Texture coordinate (float2) |
| `f` | `f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3` | Triangular face (3 vertices, each with position/texcoord/normal indices) |
| `f` | `f v1//vn1 v2//vn2 v3//vn3` | Triangular face without texture coordinates |
| `mtllib` | `mtllib path.mtl` | Material library reference |
| `usemtl` | `usemtl name` | Apply material to subsequent faces |
| `o` | `o name` | Object name (informational, not used in rendering) |

### 5.2. Face Triangulation

Faces with more than 3 vertices are not supported. All faces must be triangles.
The parser validates that each face references exactly three vertices.

### 5.3. Triangle Precomputation

After parsing, each triangle is augmented with precomputed edge vectors and dot
products for the **Möller–Trumbore ray-triangle intersection algorithm**:

```
edge1 = p1 - p0
edge2 = p2 - p0
```

These are stored in the GPU triangle buffer as `t_triangle_gpu` structs.

### 5.4. Example OBJ Snippet

```obj
# Stanford Bunny (simplified)
o Bunny
mtllib bunny.mtl

v 0.1 0.0 0.0
v 0.2 0.1 0.0
v 0.15 0.2 0.0
v 0.0 0.2 0.1
v 0.0 0.0 0.2

vn 0.0 0.0 1.0
vn 0.0 1.0 0.0
vn 1.0 0.0 0.0

vt 0.0 0.0
vt 1.0 0.0
vt 0.5 1.0

usemtl white_marble

f 1/1/1 2/2/1 3/3/1
f 1/1/1 3/3/2 4/1/2
f 1/1/1 4/1/3 5/2/3
```

---

## 6. Coordinate System and Units

- **World space** is right-handed: +X right, +Y up, +Z toward the viewer
- **All distances** are in arbitrary world units
- **Colors** are in linear RGB (no gamma correction is applied by the parser;
  the accumulation kernel does tone mapping)
- **Angles** are in degrees (FOV, rotation)
- **Texture coordinates** follow the standard OBJ convention: `u` = horizontal,
  `v` = vertical, with `(0,0)` at the bottom-left of the texture

---

## 7. Parsing Notes

- The parser is case-sensitive for keywords
- Unknown keywords are reported as parsing errors
- OBJ files are parsed recursively: `mtllib` references are resolved relative
  to the OBJ file's directory
- Materials can be defined before or after objects that reference them; the
  parser collects all materials first, then resolves references
- At minimum, a valid `.rt` file must contain exactly one `C`, one `A`, and at
  least one `L` or object