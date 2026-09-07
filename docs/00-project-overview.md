# miniRT - Project Overview

## What is miniRT?

miniRT is a **GPU-accelerated ray tracer** written in C with OpenCL - a fully interactive 3D scene editor with real-time rendering, a complete UI system, mesh loading, PBR materials, Monte Carlo path tracing, and a production-grade acceleration structure.

## Conventions

miniRT parses `.rt` scene files (see [03-scene-format.md](03-scene-format.md) for the full identifier reference) and renders via OpenCL using the **minilibx** graphics library (X11-based). The rendering engine provides 6 render modes and BVH acceleration with AABB, Sphere, and OBB bounding shapes.

## Project Scope

miniRT was built as a school project with two people in 8 months, using the minilibx library and under the 42 coding norm (norminette). It's a full-featured ray tracer, but comes with real trade-offs.

### Materials (MTL)

<table cellpadding="0" cellspacing="0" border="0" style="border:none;">
<tr><td><img src="assets/img/mat1-1.png" width="100%"></td><td><img src="assets/img/mat1-2.png" width="100%"></td></tr>
<tr><td><img src="assets/img/mat1-3.png" width="100%"></td><td><img src="assets/img/mat1-4.png" width="100%"></td></tr>
</table>

*Sample materials showing different PBR properties - metallic, dielectric, textured, and emissive surfaces.*
The full MTL parser supports PBR texture maps (albedo, normal, roughness, ambient occlusion, opacity, metalness). See [03-scene-format.md](03-scene-format.md) for the MTL keyword reference and [08-materials-and-textures.md](08-materials-and-textures.md) for the material system.

### BVH Acceleration

![BVH debug visualization](assets/img/bvh-volume-aabb.png)
*BVH debug overlay showing AABB bounding volumes around scene geometry.*

The unified BVH system provides three bounding shapes (AABB, Sphere, OBB with PCA) and three splitting algorithms (SAH, median-primitive, median-space) in a binary tree (BVH_ARITY=2). See [05-bvh.md](05-bvh.md) for the full BVH architecture, construction pipeline, and GPU traversal details.

### User Interface

![miniRT render output](assets/img/showcase-render4.png)
*Render output showcasing the full-ray traced scene with shadows, reflections, and PBR materials.*

The full UI system is built on mlxui, a custom GUI toolkit, providing a scene hierarchy list, edit panels with color pickers and sliders, render mode switching, and export controls. See [10-ui-system.md](10-ui-system.md) for the complete UI hierarchy, edit panel architecture, and selection system.

### Build and Development

The project comprises 487 C source files, 30 header files, 14 OpenCL kernel files, and 48 .mk makefiles across 7 submodules, with sanitizer support and tiered debug levels. See [02-build-system.md](02-build-system.md) for the full build system reference.

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
| File count | ~5 | **487 .c, 30 .h, 14 .cl** |