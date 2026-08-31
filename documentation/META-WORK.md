# MiniRT — Documentation Overhaul: Meta-Work Plan

> This document defines the scope, needs, and methodology for a full
> documentation overhaul of the miniRT project. It is written BEFORE any
> code indexing begins, per the user's directive.
>
> **Date:** 2026-08-31
> **Repo:** `~/workspace/minirt/`

---

## 1. What We Already Know (Pre-Indexing Survey)

A rapid structural survey of the repo has been performed. Here is the
ground-truth summary that frames the documentation work:

| Aspect | Finding |
|--------|---------|
| Language | C (gnu11), with OpenCL C kernels (.cl) for GPU |
| Total source | ~125 .c files, 8 .h files, 14 .cl files, ~9,300 lines total |
| Build | GNU Make, modular .mk includes from `mkidir/` |
| Submodules | 7: mkidir, libft, minilibx-linux, mlx_wrapper, font_renderer, mlxui, xcerrcal |
| GPU | OpenCL — 6 kernels: phong, pbr, monte_carlo, normal_debug, heat, draw_accu |
| Render modes | 6: wireframe (0), phong (1), pbr (2), monte_carlo (3), normal (4), heat (5) |
| BVH | AABB + sphere BVH; BVH2/BVH4/BVH8 branching factors; SAH subdivision |
| Scene format | .rt files (camera, ambient, materials via mtl, primitives, OBJ meshes, skybox) |
| Materials | MTL parsing: kd/ks/ke/ns/ni/opacity + texture maps (diffuse, normal, roughness, ambient, opacity, metalness) |
| Assets | OBJ meshes (AMG McLaren, Koenigsegg Jesko, Porsche, Stanford bunny, cornell box, chess, casino), textures (.ppm/.png), skybox, fonts (TTF) |
| Interactivity | minilibx window, keyboard (WASD + QE roll), mouse (yaw/pitch), render mode switching (keys 1-4, +/- for debug), BVH debug visualization |
| Sanitizers | AddressSanitizer, LeakSanitizer, UBSan — all configurable via make targets |
| Authors | Aubry Richard Jaurel & Bellissant Pablo (42 Lyon) |

---

## 2. The Original miniRT Subject (What the Project Started As)

The miniRT project is a 42 School graphics curriculum project. Its original
mandate is intentionally minimal:

> Build a basic ray tracer in C that can render simple 3D scenes with:
> - Geometric primitives (spheres, planes, cylinders)
> - Ambient and direct lighting (Phong shading)
> - A scene description file format (.rt)
> - A real-time window using minilibx
> - Camera with basic movement

The original subject constrains the student to:
- No external libraries beyond minilibx and a math library
- No GPU acceleration (CPU only)
- Simple Whitted-style ray tracing (primary ray + shadow ray + reflection)
- The .rt file format (a custom scene description)
- Norm-compliant C code (42 Norm)

---

## 3. How Far This Project Went (What We Actually Achieved)

This implementation went far beyond the original subject:

1. **GPU acceleration via OpenCL** — All ray tracing and shading is offloaded
   to the GPU via OpenCL kernels. The CPU builds the BVH and uploads buffers;
   the GPU does per-pixel ray casting, intersection, and shading.

2. **Multiple rendering modes** — Beyond the required Phong:
   - **Wireframe / rasterization** — CPU-side debug view of BVH boxes, object
     outlines, light positions
   - **Phong shading** — The baseline with per-pixel ambient + diffuse + specular
   - **PBR (Physically Based Rendering)** — Metallic-roughness workflow with
     Cook-Torrance BRDF, Fresnel (Schlick), GGX microfacet distribution, energy
     conservation, and skybox environment sampling
   - **Monte Carlo path tracing** — Stochastic progressive photon mapping with
     accumulated samples, random bouncing, refraction, and accumulation buffer
   - **Normal debug** — Visualizes surface normals as colors
   - **Heat map** — Visualizes BVH traversal depth / intersection cost

3. **BVH (Bounding Volume Hierarchy)** — Sophisticated acceleration structure:
   - AABB (Axis-Aligned Bounding Box) BVH for triangles
   - Sphere BVH for spheres
   - SAH (Surface Area Heuristic) for optimal splitting
   - Multi-ary traversal: BVH2, BVH4, BVH8
   - Interactive debug visualization (depth-based coloring, traversal count)

4. **OBJ mesh loading** — Full Wavefront OBJ parser supporting:
   - Faces, vertices, normals, UV coordinates
   - MTL material files
   - PBR texture maps (albedo, normal, roughness, metalness, opacity, ambient)
   - High-poly assets (McLaren SLR, Koenigsegg Jesko, Porsche, Stanford bunny)

5. **Texture system** — PPM and PNG loading, texture atlas/offset system for
   GPU upload, skybox environment maps

6. **Interactive camera** — Full 6-DOF camera with roll, lens aperture (DOF),
   focus distance, FOV, mouse-look, and WASD movement

7. **Accumulation rendering** — Progressive accumulation buffer for Monte Carlo
   noise reduction (multiple samples per pixel over time)

8. **Build quality tooling** — Sanitizers (ASan, LSan, UBSan), profiling
   (gprof), code inspection, fast (Ofast + march=native) builds, multi-vendor
   GCC/LLVM support

---

## 4. What I Absolutely Need (Non-Negotiable Inputs for Documentation)

Before I can produce accurate, code-verified documentation, I must read and
understand these files in depth:

### 4.1. Render Pipeline (the core)

| File(s) | Why I need it |
|---------|---------------|
| `src/loop.c` | Dispatch table — the 6 render modes and the accumulation/frame logic |
| `src/loop_hook.c` | Keyboard/mouse bindings, render mode switching, BVH debug |
| `src/calc/render/ray_tracing/phong_render.c` | Phong host-side logic |
| `src/calc/render/ray_tracing/pbr.c` | PBR host-side logic |
| `src/calc/render/ray_tracing/monte_carlo.c` | Monte Carlo host-side logic |
| `src/calc/render/ray_tracing/normal_render.c` | Normal debug host-side |
| `src/calc/render/ray_tracing/heat_render.c` | Heat map host-side |
| `src/calc/render/rasterization/wireframe_render.c` | Wireframe host-side |

### 4.2. OpenCL Kernels (the GPU math)

| File(s) | Why I need it |
|---------|---------------|
| `shader/phong.cl` | Phong kernel — the shading model to document with LaTeX |
| `shader/phong_shading.cl` | The actual Phong shading formula implementation |
| `shader/pbr.cl` | PBR kernel — Cook-Torrance, GGX, Fresnel, metallicity |
| `shader/monte_carlo.cl` | Path tracing kernel — random bounce, refraction, accumulation |
| `shader/normal_debug.cl` | Normal visualization kernel |
| `shader/heat.cl` | BVH traversal heat map kernel |
| `shader/draw_accu.cl` | Accumulation buffer → pixel conversion |
| `shader/intersect.cl` | Ray-object intersection primitives (sphere, plane, triangle, AABB) |
| `shader/calc_rays.cl` | Camera ray generation (perspective, DOF, lens) |
| `shader/sample_materials.cl` | Material sampling (texture lookup, PBR properties) |
| `shader/sample_texture.cl` | Texture coordinate sampling |
| `shader/random.cl` | PRNG for Monte Carlo |
| `shader/include/gpu.cl` | GPU struct definitions (shared across kernels) |

### 4.3. BVH Construction & Traversal

| File(s) | Why I need it |
|---------|---------------|
| `src/calc/bvh/aabb/create_bvh.c` | AABB BVH construction |
| `src/calc/bvh/aabb/divide.c` | BVH subdivision |
| `src/calc/bvh/sah/sah_algo.c` | SAH algorithm |
| `src/calc/bvh/sah/sah_subdivide.c` | SAH subdivision |
| `src/calc/bvh/sphere/create_sphere_bvh.c` | Sphere BVH construction |
| `src/calc/bvh/bvh_ary/bvh4.c` / `bvh8.c` | Multi-ary BVH packing |
| `src/calc/bvh/load_bvh.c` | BVH upload to GPU |
| `include/bvh.h` | BVH struct definitions |
| `include/bvh_sah.h` | SAH types |

### 4.4. Scene Parsing & Material System

| File(s) | Why I need it |
|---------|---------------|
| `src/parsing/parse_scene.c` | Top-level .rt parser |
| `src/parsing/rt_parser/rt_parser.c` | Line-by-line parsing |
| `src/parsing/rt_parser/mtl/parse_mtl_file.c` | MTL parsing |
| `src/parsing/rt_parser/obj/parse_obj_file.c` | OBJ parsing |
| `include/parsing.h` | Scene/material/object structs |
| `include/object.h` | Material + texture struct definitions |
| `asset/scenes/*.rt` | Example scenes to document the format |

### 4.5. OpenCL Init & Buffer Management

| File(s) | Why I need it |
|---------|---------------|
| `src/opencl.c` | OpenCL context/queue/kernel creation, buffer allocation |
| `include/minirt.h` | Main data structures (t_data, t_scene, t_buffers, t_kernel) |

### 4.6. Build System

| File(s) | Why I need it |
|---------|---------------|
| `Makefile` | Top-level build — targets, flags, linking |
| `includes.mk` | Project include paths |
| `mkidir/make_utils.mk` | Build infrastructure, compiler selection, mode detection |
| `mkidir/make_rules.mk` | Build rules, compilation patterns |
| `mkidir/sanitize.mk` | Sanitizer configuration |
| `mkidir/colors.mk` | Terminal color macros for build output |
| `src/srcs.mk` | Source file tree |
| `.gitmodules` | Submodule definitions |
| All `*.mk` files in subdirs | Per-module source includes |

### 4.7. Camera & Interaction

| File(s) | Why I need it |
|---------|---------------|
| `src/camera_utils.c` | Camera math (basis vectors, FOV, DOF) |
| `src/camera_move.c` | Movement/rotation logic |
| `include/render.h` | t_camera struct |

---

## 5. All Potential Needs (Possible, Not Guaranteed)

These are things that MIGHT be needed depending on what the code reveals. I
will determine necessity during the indexing phase.

### 5.1. Possible Documentation Gaps

| Need | Trigger Condition |
|------|-------------------|
| Document the MTL file format spec | If the parser supports a non-trivial subset of MTL |
| Document the OBJ file format spec | If custom parsing logic is non-obvious |
| Document the .rt file format spec | If there are undocumented keywords (e.g., `sky`, `obj`, `mtl`) |
| Document the PPM/PNG texture loading | If there's a custom texture loader |
| Document the BVH traversal algorithm pseudocode | If the traversal is non-standard |
| Document the SAH cost function with LaTeX | If the SAH math is implemented |
| Document the refraction model (Snell's law) | If monte_carlo.cl does refraction |
| Document the GGX/Trowbridge-Reitz microfacet distribution | If pbr.cl uses it |
| Document the random number generator (PRNG) | If random.cl has a custom PRNG |
| Document the accumulation/progressive rendering math | If draw_accu or monte_carlo does averaging |
| Document the lens/camera model (thin lens DOF) | If calc_rays.cl simulates aperture |
| Document the export-to-PPM feature | If export_to_ppm.c is functional |

### 5.2. Possible make help Needs

| Need | Trigger Condition |
|------|-------------------|
| Document the `inspect` target (LLDB?) | If inspect mode has specific flags |
| Document the `profile` target (gprof) | If PROFILE_FLAGS are set |
| Document the sanitizer runtime env vars | If ASAN_OPTIONS/LSAN_OPTIONS are set |
| Document the `print-%` debug target | If it exists (it does) |
| Document the `WINDOWLESS` / `FULLSCREEN` / `RESIZEABLE` flags | If they affect rendering |
| Document the `PERF` flag | If it's used |
| Document the `CL_TARGET_OPENCL_VERSION` flag | If it affects OpenCL compilation |
| Document the machine-ID based compiler selection | If the Makefile has machine detection |
| Document the `NPROC` parallelism flag | If make uses -jN |

### 5.3. Possible README Needs

| Need | Trigger Condition |
|------|-------------------|
| Prerequisites (OpenCL, X11, etc.) | If the build requires specific system packages |
| Installation instructions | If submodules need special handling |
| Usage examples (which .rt scenes to run) | If the scenes demonstrate different features |
| Key bindings reference | If there are many controls |
| Performance notes | If there are known perf characteristics per mode |
| Screenshots / render examples | If we want to show what each mode looks like |

### 5.4. Possible Diagrams (Mermaid)

| Diagram | Purpose |
|---------|---------|
| Architecture overview | Module relationships, data flow |
| Render pipeline flow | Scene → BVH → GPU → pixel buffer → display |
| Build dependency chain | Submodule build order (MLX → libft → wrapper → UI → ...) |
| OpenCL data flow | Host buffers → GPU buffers → kernels → framebuffer |
| BVH construction | SAH subdivision → BVH2/4/8 → GPU upload |
| Scene parsing | .rt → tokenizer → parser → scene struct → GPU upload |
| Class diagram | Core structs (t_data, t_scene, t_camera, t_ray, t_hit, t_mat, t_object) |

---

## 6. Deliverables Plan

### 6.1. `documentation/` folder

A structured, professional documentation directory:

```
documentation/
  00-project-overview.md       — What miniRT is, the original subject, how far we went
  01-architecture.md           — System architecture (with Mermaid diagrams)
  02-build-system.md           — Makefile chain, submodules, flags, targets
  03-scene-format.md           — .rt file format spec + .mtl + .obj
  04-render-modes/
    00-overview.md             — Mode switching, dispatch table
    01-wireframe.md            — Wireframe/rasterization debug mode
    02-phong.md                — Phong shading (with LaTeX)
    03-pbr.md                  — PBR / Cook-Torrance (with LaTeX)
    04-monte-carlo.md          — Path tracing (with LaTeX)
    05-normal-debug.md         — Normal visualization
    06-heat-map.md             — BVH heat map
  05-bvh.md                    — BVH construction, SAH, traversal (with LaTeX)
  06-opencl-integration.md     — GPU pipeline, kernels, buffer management
  07-camera-and-interaction.md — Camera model, controls, DOF
  08-materials-and-textures.md — MTL, texture maps, PBR properties
  09-asset-catalog.md          — What's in asset/ and how to use it
```

### 6.2. `make help` target

A clean, comprehensive `make help` that documents:
- All make targets (all, fast, debug, inspect, profile, san-mem, san-leak,
  san-ub, re, refast, redebug, reinspect, reprofile, resan-*, clean, fclean,
  help, print-%, bonus)
- The submodule build chain (which library depends on which)
- All build flags (DEBUG_LVL, FAST, WIDTH, HEIGHT, PERF, FULLSCREEN,
  RESIZEABLE, WINDOWLESS, NPROC, CL_TARGET_OPENCL_VERSION, VERBOSE,
  PROFILE, etc.)
- Environment variables for sanitizers (ASAN_OPTIONS, LSAN_OPTIONS, UBSAN_OPTIONS)

### 6.3. `README.md`

A clean, professional README that covers:
- What miniRT is
- The original 42 subject goal
- How far the project went (OpenCL GPU, PBR, Monte Carlo, BVH, OBJ, etc.)
- Feature list
- Prerequisites
- Quick start (build + run)
- Render modes table
- Key bindings
- Link to `documentation/` for full docs
- Mermaid architecture diagram

---

## 7. Methodology

### Phase 1: Deep Code Indexing (Parallel Delegation)

I will spawn parallel sub-agents to index each subsystem:
- **Agent A**: Render pipeline + OpenCL kernels (read every .cl and render .c)
- **Agent B**: BVH + scene parsing + materials (read every bvh/parsing/mtl file)
- **Agent C**: Build system (read every .mk, Makefile, submodule Makefile)

Each agent returns a structured analysis: what the code does, which formulas
are implemented, any quirks, and the exact line references for documentation.

### Phase 2: Documentation Writing (Parallel Delegation)

Once indexed, I will spawn sub-agents to write each documentation file in
parallel, using the analysis from Phase 1 as source material.

### Phase 3: make help + README (Sequential)

I'll write the `make help` target and README myself after the documentation
is complete, so the README can reference the docs.

### Phase 4: Verification (Delegated)

A sub-agent will verify:
- All LaTeX formulas match the actual code
- All Mermaid diagrams are syntactically valid
- All file paths referenced in docs actually exist
- `make help` output is accurate against the real Makefile

---

## 8. Constraints & Guardrails

- **Read-only**: No pushes to the remote repo. All output is local in
  `~/workspace/minirt/`.
- **C codebase**: Documentation must reflect actual C code behavior, not
  theoretical ray tracing.
- **LaTeX**: All math formulas use LaTeX notation (inline `$...$` and
  block `$$...$$`).
- **Mermaid**: All diagrams use Mermaid syntax.
- **No fabrication**: Every formula, every algorithm description, every flag
  must be traceable to actual code. If the code doesn't implement something,
  we don't document it as if it does.

---

## 9. Open Questions (May Need User Input)

1. **Should the documentation be in English or French?** (The codebase has
   French 42 header comments, but the project authors are French.)
   → Defaulting to English (international standard) unless told otherwise.

2. **Should `make help` be a new target or should I replace the existing
   minimal `help` target?** → I'll replace the existing one with a
   comprehensive version.

3. **Should the README include screenshots?** → I can't generate actual
   renders (no display server), so the README will reference the documentation
   for visual details. If the user has renders to include, they can be added
   later.

4. **Level of LaTeX detail?** → I'll aim for a level suitable for a graphics
   engineer who wants to understand the math but isn't a PhD — clear
   derivations, not just final formulas.

---

## 10. Next Action

Proceed to Phase 1: Deep Code Indexing via parallel sub-agents.
