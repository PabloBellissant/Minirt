# MiniRT — Project Overview

## What is MiniRT?

MiniRT is a **GPU-accelerated ray tracing renderer** written in C with OpenCL
kernels. It began as a 42 School graphics project — a basic CPU ray tracer with
Phong shading and simple primitives — and evolved into a full physically based
rendering pipeline that pushes far beyond the original subject requirements.

The result is closer to a **miniature Blender** than a basic ray tracer: it
includes a complete custom scene format parser (`.rt`), Wavefront OBJ and MTL
file parsing for meshes and materials, a UI layer with TTF font rendering
written in C, real-time selection and editing of scene objects, scene import
and export (round-trip), and full debug visualization tools for the
acceleration structures.

**Authors:** Aubry Richard Jaurel & Bellissant Pablo (42 Lyon)
**Language:** C (gnu11) + OpenCL C
**Lines of code:** ~9,300 (125 `.c` + 8 `.h` + 14 `.cl`)

---

## Original 42 School Subject Goal

The 42 School `miniRT` project asks students to write a **minimal ray tracer**
in C that renders a scene read from a `.rt` configuration file. The required
features are:

- Parse a simple scene description file with cameras, ambient light, point
  lights, spheres, and planes.
- Render the scene using **Phong shading** (ambient + diffuse + specular).
- Support parallel (but not directional) lights.
- Render in real time in a window (minilibx).
- Handle basic keyboard controls (camera movement).

The subject intentionally limits the scope to a **CPU-only, single-ray-per-pixel
renderer** with no acceleration structures, no textures, no materials beyond
basic color, and no physically based lighting.

---

## What This Implementation Does

This implementation goes far beyond the original subject in nearly every
dimension:

### Rendering Pipeline

| Feature | Original Subject | This Implementation |
|---|---|---|
| Render engine | CPU, single-threaded | **OpenCL GPU** (parallel NDRange) |
| Shading model | Phong only | **Phong, PBR, Monte Carlo path tracing**, normal debug, heat map |
| Acceleration | None | **BVH** with SAH (Surface Area Heuristic), BVH2/4/8 variants |
| Anti-aliasing | None | **Progressive accumulation** (samples over multiple frames) |
| Depth of field | None | **Thin lens model** with focus distance and aperture |
| Reflections | None | **Recursive** (up to 4 bounces) in PBR mode |
| Refractions | None | **Snell's law** with total internal reflection |
| Microfacet sampling | None | **GGX/Trowbridge-Reitz** importance sampling |
| Chromatic dispersion | None | **Wavelength-dependent IOR** modulation in Monte Carlo mode |
| Shadow rays | None | **Yes** (check for occlusion between hit point and light) |

### Scene Description

| Feature | Original Subject | This Implementation |
|---|---|---|
| Primitives | Sphere, plane | Sphere, plane, **triangle (OBJ meshes)** |
| Materials | Simple color | **Full PBR material system** (Kd, Ks, Ke, Ns, Ni, d, Pr, Pm) with **MTL file parsing** |
| Textures | None | **Diffuse, normal, roughness, ambient, opacity, metalness** maps |
| Scene format | Simple keyword parser | **Custom `.rt` format parser** with full keyword validation |
| OBJ/MTL support | None | **Wavefront OBJ** with MTL materials, triangulated faces |
| Skybox | None | **Skybox texture** (PPM/PNG) |

### Interactive Features

| Feature | Original Subject | This Implementation |
|---|---|---|
| Render modes | 1 | **6 modes** (wireframe, Phong, PBR, Monte Carlo, normal, heat) |
| Camera control | Basic movement | **6-DOF** (WASD + up/down + roll + mouse look) |
| BVH debugging | None | **BVH overlay** with toggle, depth control, mode switching, color cycling |
| Scene export | None | **Export to .rt** (round-trip) and **PPM** screenshot |
| UI layer | None | **TTF font rendering**, real-time object selection and editing |

### Architectural Features

| Feature | Original Subject | This Implementation |
|---|---|---|
| CPU/GPU split | CPU only | **Hybrid**: CPU rasterized wireframe + GPU ray traced everything else |
| BVH construction | None | **Two systems**: sphere BVH (hierarchical merging) + AABB BVH (SAH binning) |
| BVH branching | None | **BVH2** (stackless skip pointers), **BVH4/8** (stack-based wide traversal) |
| Norm compliance | 42 Norm | Full 42 Norm compliance throughout |
| Debug visualization | None | **BVH debug overlay** (bounding boxes, depth filtering, color palette cycling, mode switching) |

---

## Key Technical Highlights

1. **OpenCL GPU acceleration** — All ray tracing (Phong, PBR, Monte Carlo,
   normal debug, heat map) runs on the GPU via `clEnqueueNDRangeKernel` with
   one work-item per pixel. The kernel source is embedded in the binary as a
   C string literal and compiled at runtime.

2. **BVH with SAH** — The AABB BVH is constructed using the Surface Area
   Heuristic with 16-bin axis-aligned partitioning, minimizing expected
   traversal cost. The BVH can be flattened to BVH2 (stackless skip-pointer
   traversal) or packed into BVH4/BVH8 (wide-node stack-based traversal).

3. **Monte Carlo path tracing** — Uses GGX microfacet importance sampling
   with up to 4 bounces per path. Chromatic dispersion modulates the index
   of refraction based on a wavelength derived from the path's accumulated
   color, producing rainbow effects in transparent materials.

4. **Progressive rendering** — The accumulation buffer accumulates samples
   across frames. When the camera moves or a render parameter changes, the
   buffer resets. The final pixel color is `accumulation / frame_count`.

5. **Dual BVH systems** — Two independent BVH implementations coexist:
   a sphere-based BVH (hierarchical sphere merging) and an AABB-based BVH
   (SAH binning). The user can switch between them at runtime via the
   `bvh_mode` parameter.

6. **6 render modes** — A dispatch table routes the current render mode to
   the appropriate function: wireframe (CPU rasterized), Phong, PBR, Monte
   Carlo, normal debug, and heat map. Keys 1–6 switch between them.

---

## Comparison Summary

```
Original Subject          →    This Implementation
────────────────────────────────────────────────────
CPU only                  →    OpenCL GPU acceleration
Phong only                →    Phong + PBR + Monte Carlo + debug modes
No acceleration           →    BVH with SAH (BVH2/4/8)
No materials              →    Full PBR material system with textures
No textures               →    6 texture map types + skybox
Spheres + planes only     →    + OBJ triangle meshes
No reflections/refractions →   Up to 4 bounces, Snell's law, GGX, dispersion
Single sample per pixel   →    Progressive accumulation
Basic camera              →    6-DOF + depth of field
```

The result is a renderer that comfortably occupies the space between a 42
School graphics project and a production-level physically based renderer,
demonstrating GPU compute, acceleration structures, physically based shading,
and Monte Carlo integration — all in under 10,000 lines of C.