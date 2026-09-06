# miniRT — GPU Ray Tracer & Real-Time Scene Editor

**miniRT** is a real-time GPU-accelerated ray tracing engine written entirely
in C with OpenCL. What started as the standard 42 School graphics project
(a minimal CPU ray tracer with Phong shading and a handful of primitives)
grew into something far closer to a **miniature Blender** than a homework
assignment: a full scene editor with UI, font rendering, real-time selection
and editing, import/export, multiple BVH acceleration structures, and six
rendering modes — all in pure C with no external rendering libraries.

The engine parses `.rt` scene files (a custom format), loads Wavefront
`.obj` meshes with `.mtl` material libraries, supports PBR textures (diffuse,
normal, roughness, ambient occlusion, opacity, metalness), and renders on the
GPU via OpenCL with progressive accumulation for noise reduction. The CPU
side handles scene parsing, BVH construction, an interactive UI layer with
font rendering and selection, and a wireframe debug visualizer.

---

## Architecture

```mermaid
flowchart TD
    A[".rt Scene File"] --> B["Parser"]
    B --> C["Scene Data"]
    C --> D["BVH Builder"]
    C --> E["Camera Setup"]
    C --> F["GPU Buffer Upload"]
    D --> G["BVH2 / BVH4 / BVH8<br/>Sphere / AABB / OBB"]
    G --> F
    E --> H["Render Loop"]
    F --> H
    H --> I{"Wireframe?"}
    I -- Yes --> J["CPU Rasterizer"]
    I -- No --> K["OpenCL GPU Kernel"]
    K --> L{"Mode"}
    L -- Phong --> M["Phong Shading"]
    L -- PBR --> N["PBR: Fresnel + Refraction"]
    L -- Monte Carlo --> O["Path Tracing: GGX + Dispersion"]
    L -- Normal --> P["Normal Debug"]
    L -- Heat --> Q["BVH Depth Heat Map"]
    M --> R["Accumulation Buffer"]
    N --> R
    O --> R
    P --> R
    Q --> R
    J --> R
    R --> S["draw_accu: Normalize ÷ exposure"]
    S --> T["minilibx Display"]
    T --> U["UI Layer<br/>panels + selection + editing"]
    U --> V["Screen Output"]
    U -.->|"edit"| C
    U -.->|"edit"| E
    V --> H
```

### Extended Render Loop Detail

```mermaid
flowchart TD
    START["loop()"] --> MOVE["handle_camera_move()"]
    MOVE --> CHECK{"cam_has_moved()<br/>or render_changed()?"}
    CHECK -->|"Yes"| ZERO["Zero accumulation buffer<br/>Reset frame to 1"]
    CHECK -->|"No"| FRAME["frame++"]
    ZERO --> FRAME
    
    FRAME --> RENDER["render_func[*mode]()"]
    RENDER -->|"mode 0: wireframe"| CPU["CPU rasterize objects"]
    RENDER -->|"mode 1-5: GPU"| GPU_DISPATCH["clEnqueueNDRangeKernel<br/>2D global = {WIDTH, HEIGHT}"]
    GPU_DISPATCH --> ACCU_KERNEL["draw_accu kernel<br/>accu ÷ max(1, frame×exposure)<br/>×255 → packed int"]
    ACCU_KERNEL --> READBACK["clEnqueueReadBuffer(img → host)"]
    CPU --> READBACK
    
    READBACK --> DRAW_MLX["mlx_put_data_addr"]
    DRAW_MLX --> DRAW_SEL["rasterize_selected()<br/>Highlight selected objects"]
    DRAW_SEL --> EXPORT_TASK{"export_render_task?"}
    
    EXPORT_TASK -->|"Yes"| EXPORT["Hide UI → render →<br/>export_to_ppm → show UI"]
    EXPORT_TASK -->|"No"| FPS["update_fps()"]
    
    EXPORT --> FPS
    FPS --> DRAW_SEL_BOX["draw_select()<br/>Selection rectangle"]
    DRAW_SEL_BOX --> UI_LAYER["render_hierarchy()<br/>Full UI tree"]
    UI_LAYER --> BVH_DEBUG["debug_rasterize_bvh()<br/>BVH box overlay"]
    BVH_DEBUG --> PUT_IMAGE["mlx_put_image_to_window"]
    PUT_IMAGE --> LOOP_END["→ loop() again"]
```

---

## The Original Subject

The 42 School **miniRT** project brief calls for a minimal CPU-based ray
tracer rendering spheres, planes, and cylinders with **Phong shading**
(ambient + diffuse + specular). Scenes are defined in a `.rt` text format
(camera, ambient light, point lights, primitives with material references).
The windowing library is **minilibx** (a simplified X11 wrapper). The subject
explicitly forbids GPU acceleration, external rendering libraries, and
advanced shading models.

**Don't use this as a reference.** This is a school project where we went
down the rabbit hole — way too far. The codebase isn't as clean as it could
be because we had to follow the 42 norminette (a strict coding standard
enforced by an automated linter), which is great for learning discipline
but genuinely disabling at this scale. The base graphics library (minilibx)
is also a significant limitation — it's a barebones X11 wrapper with no
hardware acceleration for 2D, meaning every UI element from TTF font
rendering to UI components is CPU-drawn, which absolutely destroys
performance.

But we wanted to do something really good and really fast, and we almost
ended up building a Blender clone.

---

## How Far We Went

This implementation went far beyond the base subject in nearly every
dimension:

- **OpenCL GPU acceleration** — All ray tracing runs on the GPU. The CPU
  handles only scene parsing, BVH construction, and the wireframe debug view.
- **6 render modes** — Wireframe (CPU), Phong, PBR, Monte Carlo path tracing,
  normal debug, and BVH heat map (all GPU).
- **PBR** — Cook-Torrance microfacet BRDF, Schlick Fresnel, GGX normal
  distribution, metallic/roughness workflow with texture maps.
- **Monte Carlo path tracing** — Importance-sampled GGX, multi-bounce rays,
  chromatic dispersion (wavelength-dependent IOR), progressive accumulation.
- **Multiple BVH types** — Sphere-based BVH (hierarchical sphere merging),
  AABB BVH with SAH (Surface Area Heuristic, 16-bin partitioning), and
  OBB BVH with PCA. All three support BVH2, BVH4, and BVH8 branching factors
  with stackless (BVH2) and stack-based (BVH4/8) GPU traversal.
- **Full BVH debug visualization** — Toggle BVH bounding box overlays, adjust
  displayed depth, cycle color palettes (10 palettes), switch between BVH
  modes in real time.
- **OBJ + MTL loading** — Wavefront `.obj` meshes with `.mtl` materials,
  triangulated faces, vertex normals, UV coordinates, and full PBR texture
  maps.
- **Scene import & export** — Parse `.rt` files into the engine and export
  them back out. Round-trip your scenes.
- **UI and real-time editing** — An in-engine UI layer with font rendering
  (TTF via a custom font renderer), edit panels with sliders, colorpickers,
  and texture selectors, a scene hierarchy list, drag selection, and real-time
  property editing of objects, cameras, lights, and materials — all in C.
- **Cylinder primitive** — Full cylinder support via the `cy` keyword in
  `.rt` scene files, with configurable height, diameter, and material.
- **OBB BVH with PCA** — Oriented Bounding Box BVH built with Principal
  Component Analysis for tighter-fitting, rotation-aware bounds.
- **Exposure control** — Real-time exposure adjustment via `F5` (increase)
  and `F6` (decrease), applied to the accumulation buffer at render time.
- **Mesh object type** — `.obj` meshes loaded as a first-class object type
  (`t_mesh`) with full `.mtl` material libraries and PBR texture maps.
- **Interactive 6-DOF camera** — WASD + Space/Shift + QE roll + mouse look,
  with depth-of-field (thin lens aperture and focal distance).
- **Sanitizers & profiling** — AddressSanitizer, LeakSanitizer, UBSan, gprof
  profiling, and debug/inspection builds — all selectable via make targets.
- **UI mode cycling** — `M` key cycles through full UI ↔ minimal (render
  switch only) ↔ hidden modes.

---

## Reality Check

For a C project made in 8 months by two people with an obscure graphics
library and a strict norm, this is still pretty great. But if we're being
honest, there are real issues and a graveyard of scrapped ambitions.

### Known Issues

- **UI performance** — All UI elements (TTF font rendering, UI components,
  panels, sliders, color pickers) are CPU-drawn through minilibx. There's no
  GPU-accelerated 2D path. This absolutely destroys performance when the UI is
  visible. The render itself is on GPU, but every frame the UI is redrawn pixel
  by pixel on the CPU.
- **Portability** — The project was developed on 42 campus iMacs with
  self-compiled, somewhat wanky OpenCL packages. Portability is a real issue.
  The build system has machine-ID detection to switch compilers between known
  campus machines and everything else, which should tell you something.
- **Obscure C paradigms** — Some parts of the codebase use abusive patterns
  to mimic OOP in C (notably in `mlxui` for component polymorphism and in
  `mlx_wrapper` for key/mouse hook actions). This can cause compilation
  issues on certain compiler versions — it works on campus because the
  compiler is old enough to let it slide.
- **Norminette constraints** — The 42 norm enforces a single coding style
  (max 25 lines per function, no for loops, specific indentation, etc.).
  Great for learning discipline, disabling at 251 source files.

### What We'd Change

If we could redo it from scratch, a lot would change — the architecture
would be cleaner, the UI would not be CPU-drawn, and we'd use a proper
graphics abstraction instead of minilibx.

### Scrapped Features

A lot of infrastructure was designed for features that were never
implemented:

- **BVH UI panel** — A full UI section was planned for generating on-the-fly
  BVH types, letting the user pick shapes, splitting algorithms, and arity
  from the interface. Scraped to keep the BVH system simple.
- **Multiple BVH arities** — BVH4 and BVH8 (quad and octree branching) were
  designed and partially implemented. Removed in favor of a single binary
  tree (BVH_ARITY=2) for simplicity.
- **DOP shapes** — Discrete Oriented Polytopes (DOP-4, DOP-6, DOP-8) were
  planned as additional bounding shapes alongside AABB, Sphere, and OBB.
  Never implemented.
- **Split/merge algorithms** — Additional algorithms for determining optimal
  splits and merges of bounding volumes were planned. Only SAH,
  median-primitive, and median-space made it in.
- **Full object editing** — Way more editing options were planned for meshes
  and primitives (per-vertex editing, material assignment UI, transform
  gizmos). Only basic property editing is available.
- **Camera and light editing** — More comprehensive camera and light editing
  panels were planned.
- **Full scene hierarchy** — A complete scene hierarchy tree (like Blender's
  outliner) was planned. A simplified scene list exists instead.
- **World panel** — A world settings panel was meant to exist for changing
  global settings like ambient light color and intensity.
- **Dissociated camera/player movement** — Like Blender's separate camera
  object vs. viewport navigation. Never implemented.
- **PNG parser** — A PNG texture parser was planned for certain textures.
  Only PPM/PFM is supported.
- **Grid world, anchor rotation, movement arrows** — Grid floor display,
  rotation around a world anchor point, and position/rotation movement
  arrows on selected objects (like Blender gizmos). All planned, none
  implemented.

---

## Prerequisites

| Dependency | Notes |
|---|---|
| OpenCL (1.2+, target 3.0) | `libOpenCL.so.1` — GPU runtime |
| X11 development headers | Windowing via minilibx |
| libXtst (XTEST extension) | Mouse confinement / input |
| Xrandr | Display resolution detection |
| gcc (12 or 14) | Or compatible C compiler |
| GNU Make | Build system |

On Debian/Ubuntu:

```bash
sudo apt install mesa-opencl-icd opencl-headers libxtst-dev libxext-dev \
                 libx11-dev libxrandr-dev gcc-12 make
```

---

## Quick Start

```bash
# Clone the repository
git clone <repository-url> minirt
cd minirt

# Initialize and update all submodules (7 total + minirt-assets)
git submodule init
git submodule sync
git submodule update --remote

# Build (default: no optimization)
make

# Or build with optimizations
make fast

# Run a scene
./MiniRT asset/scenes/template.rt
```

A window opens showing the scene. Use the keyboard and mouse to explore.

### Testing Assets

The **minirt-assets** submodule (initialized via `git submodule update --remote`
above) contains large OBJ models and high-resolution textures for miniRT:

[https://github.com/ketodin/minirt-assets](https://github.com/ketodin/minirt-assets)

---

## Render Modes

| Mode | Key | Description |
|------|-----|-------------|
| **Wireframe** | `1` | CPU rasterized debug view — BVH boxes, object outlines, light positions |
| **Phong** | `2` | GPU Phong shading (ambient + diffuse + specular + emissive + shadows) |
| **PBR** | `3` | GPU physically based rendering (Fresnel, reflection, refraction, bounces) |
| **Monte Carlo** | `4` | GPU path tracing (GGX sampling, chromatic dispersion, progressive accumulation) |
| **Normal Debug** | `-` | GPU normal visualization (surface normals mapped to RGB) |
| **Heat Map** | `=` | GPU BVH traversal depth heat map (10 color palettes) |

---

## Key Bindings

### Camera

| Key | Action |
|-----|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Move left / right |
| `Space` / `Shift` | Move up / down |
| `Q` / `E` | Roll left / right |
| `Ctrl` (held) | Double movement speed |
| Mouse | Yaw / pitch look |
| `K` | Toggle mouse focus (confine pointer) |

### Depth of Field

| Key | Action |
|-----|--------|
| `T` / `G` | Increase / decrease focus distance |
| `Y` / `H` | Increase / decrease lens radius (aperture) |

### Render Mode

| Key | Action |
|-----|--------|
| `1` – `4` | Switch render mode (wireframe, Phong, PBR, Monte Carlo) |
| `-` / `=` | Switch to normal debug / heat map mode |

### BVH Debug

| Key | Action |
|-----|--------|
| `V` | Toggle BVH debug overlay (bounding box visualization) |
| `Up` / `Down` | Increase / decrease displayed BVH depth |
| `Left` / `Right` | Switch BVH mode (sphere BVH / AABB SAH BVH / OBB PCA BVH) |
| `C` | Cycle BVH color palette offset (0-9) |

### UI / Display

| Key | Action |
|-----|--------|
| `M` | Cycle UI mode: full UI → minimal (render switch only) → hidden |
| `F5` / `F6` | Increase / decrease exposure (×1.3 / ÷1.3) |

### Export

| Key | Action |
|-----|--------|
| `F11` | Export current scene to `.rt` file |
| `F12` | Schedule render task (hides UI, exports clean screenshot to PPM) |

---

## Screenshots

> Place rendered screenshots and GIFs in the `screenshots/` folder.

| Render Mode | Preview |
|---|---|
| Wireframe | ![Wireframe](screenshots/wireframe.png) |
| Phong | ![Phong](screenshots/phong.png) |
| PBR | ![PBR](screenshots/pbr.png) |
| Monte Carlo | ![Monte Carlo](screenshots/monte_carlo.png) |
| Normal Debug | ![Normal Debug](screenshots/normal_debug.png) |
| Heat Map | ![Heat Map](screenshots/heat_map.png) |

---

## Build Options

| Flag | Default | Description |
|------|---------|-------------|
| `WIDTH` | 500 | Window width (or `MAX_WIDTH` if `FULLSCREEN=1`) |
| `HEIGHT` | 500 | Window height (or `MAX_HEIGHT` if `FULLSCREEN=1`) |
| `FULLSCREEN` | 0 | Use full screen resolution (detected via `xrandr`) |
| `RESIZEABLE` | 0 | Allow window resize |
| `WINDOWLESS` | 0 | Headless (no window) mode |
| `PERF` | 0 | Performance mode flag (passed to submodules) |
| `NPROC` | auto | Number of CPU cores for parallel work (`$(nproc)`) |
| `VERBOSE` | 0 | Show compile commands in build output |
| `CL_TARGET_OPENCL_VERSION` | 300 | OpenCL target version macro |
| `DEBUG_LVL` | 0 | Tiered debug level — see below |
| `FAST` | auto | Set by `make fast`; adds `-Ofast -march=native -mtune=native -msse3` |

### Debug Levels (`DEBUG_LVL`)

The build system uses a **tiered debug level** that controls which submodules
compile with debug symbols. Each submodule has its own threshold — when
`DEBUG_LVL` is greater than or equal to a submodule's threshold, that
submodule compiles with `DEBUG=1` (which enables debug build messages, debug
symbols, and any submodule-specific debug code paths).

| `DEBUG_LVL` | Debugs | Threshold |
|-------------|--------|-----------|
| `0` | Nothing (release build) | — |
| `1` | All submodules | `make debug` sets this |
| `2` | + mlx_wrapper | `DEBUG_MLXW = 2` |
| `3` | + font_renderer | `DEBUG_FTRDR = 3` |
| `4` | + mlxui | `DEBUG_MLXUI = 4` |
| `5` | + miniRT itself (the main binary) | `DEBUG_MINIRT = 5` |

So `make debug` (which sets `DEBUG_LVL=1`) enables debug mode in **every**
submodule at once. For more targeted debugging, set `DEBUG_LVL` to a specific
level — e.g. `make DEBUG_LVL=3` to debug libft, mlx_wrapper, and
font_renderer but not mlxui or the main binary.

The `DEBUG` macro is also passed as `-D DEBUG=0` or `-D DEBUG=1` to the C
compiler, so source code can use `#if DEBUG` guards for debug-only code
paths. Additionally, the build output changes: in debug mode, build messages
are printed in yellow with a warning prefix instead of the normal purple.

### Sanitizer Targets

For memory and undefined-behavior debugging, use the sanitizer targets
instead. These compile with `-g3 -O1` and the appropriate `-fsanitize=`
flags, then print the required `ASAN_OPTIONS` / `LSAN_OPTIONS` / `UBSAN_OPTIONS`
environment variables at the end of the build so you can export them before
running:

```bash
make san-mem    # AddressSanitizer (heap/stack overflow, use-after-free)
make san-leak   # LeakSanitizer (memory leak detection + ASan)
make san-ub     # Undefined Behavior Sanitizer (all UB checks)
```

The build output will show the exact `export` command to run before launching
the binary. See `make help` for the full sanitizer option strings.

### Other Build Modes

| Target | Flags | Use case |
|--------|-------|----------|
| `all` | `-Wall -Werror -Wextra -std=gnu11` | Default build |
| `fast` | + `-Ofast -march=native -mtune=native -msse3` | Optimized build |
| `inspect` | + `-g3` (no optimization) | LLDB/gdb debugging |
| `profile` | + `-g3 -pg` | gprof profiling |
| `debug` | `DEBUG_LVL=1`, `-g3` | Debug symbols in all submodules |

Run `make help` for the complete list.

---

## Documentation

Full documentation — architecture, data structures, mathematical formulas
(LaTeX), build system reference, render mode deep dives, BVH construction,
OpenCL integration, camera model, material system, and asset catalog — is
in the [`documentation/`](documentation/) folder.

---

## Authors

- **Aubry Richard Jaurel** — [jaubry--](https://github.com/jaubry--) (42 Lyon)
- **Bellissant Pablo** — [pabellis](https://github.com/pabellis) (42 Lyon)

Built at 42 School Lyon, France.