# miniRT - Project Overview

## What is miniRT?

miniRT is a **GPU-accelerated ray tracer** written in C with OpenCL - a fully interactive 3D scene editor with real-time rendering, a complete UI system, mesh loading, PBR materials, Monte Carlo path tracing, and a production-grade acceleration structure.

## Conventions

miniRT parses `.rt` scene files (see [03-scene-format.md](03-scene-format.md) for the full identifier reference) and renders via OpenCL using the **minilibx** graphics library (X11-based). The rendering engine provides 6 render modes and BVH acceleration with AABB, Sphere, and OBB bounding shapes.

## Build and Development

The project comprises 487 C source files, 30 header files, 14 OpenCL kernel files, and 48 .mk makefiles across 7 submodules, with sanitizer support and tiered debug levels. See [02-build-system.md](02-build-system.md) for the full build system reference.

## Feature Comparison

| Feature | 42 Subject miniRT | Our miniRT |
|---|---|---|
| Render backend | CPU | **GPU (OpenCL)** |
| Shading | Phong | **Phong, PBR (Fresnel/GGX), Monte Carlo** |
| Render modes | 1 | **6** (wireframe, Phong, PBR, Monte Carlo, normal, heat) |
| Acceleration | None | **BVH** (AABB/Sphere/OBB + SAH/median) |
| Primitives | Sphere, Plane, Cylinder | Sphere, Plane, **Cylinder**, **Mesh (OBJ)** |
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
