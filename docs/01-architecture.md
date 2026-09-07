# miniRT - System Architecture

## Overview

![Architecture overview diagram](assets/svg/render-pipeline.svg)
*High-level system architecture showing the three layers: main binary, library submodules, and assets. The data flow moves from scene parsing through BVH construction to GPU rendering and display.*

miniRT is organized into three layers: the **main binary** (`src/`), **library submodules** (`lib/`), and **assets** (`minirt-assets/`). The binary reads a `.rt` scene file, parses it into an in-memory scene graph, transfers data to the GPU, and runs a render loop that dispatches OpenCL compute kernels.

## Data Hierarchy - `t_data`

The central state object `t_data` (defined in `include/minirt.h`) holds every subsystem:

```c
typedef struct s_data
{
    t_opencl    cl;        // OpenCL state (platform, device, queue, kernels, GPU buffers)
    t_buffers   buffers;   // CPU-side buffers: addr (uint*) + accu (t_vec3*)
    t_params    params;    // Render mode ptr, BVH depth, color offset, exposure, UI mode
    t_keys      keys;      // Keyboard state (forward/left/right/backward/upward/roll)
    t_mouse     mouse;     // Mouse look (yaw/pitch target & current)
    t_mlx       *mlx;      // minilibx instance (window, image, display)
    t_vec2i     screen;    // Screen resolution
    t_scene     scene;     // Full scene description
    t_ui        ui;        // Complete UI state
}               t_data;
```

### `t_scene` - Scene Description

![Scene data flow diagram](assets/img/showcase-render5.png)
*Data flow from .rt file parsing into the in-memory t_scene structure, then uploaded to the GPU for rendering.*

```c
typedef struct s_scene
{
    t_rgb           ambient;       // Ambient light (float RGB x ratio)
    t_camera        camera;        // Camera: pos, rot, forward/right/up, FOV, DOF params
    char            *name;         // Scene file name
    t_vector        objects;       // All scene objects (t_object union array)
    t_vector        light;         // Point lights
    int             plane_count;   // Number of planes (for GPU dispatch)
    t_vector        texture;       // Loaded textures (t_texture / t_img_data)
    t_vector        mat;           // Material definitions
    t_vector        mtl_list;      // Loaded MTL file paths (strings)
    t_vector        mesh;          // Loaded mesh instances (t_mesh: offset, count, transform)
    t_bvh_engine    bvh;           // BVH acceleration structure
    t_mlx           *mlx;          // Back-link to mlx
    int             skybox_tex;    // Index of skybox texture (-1 if none)
    // GPU buffers (cl_mem):
    cl_mem          spheres;
    cl_mem          triangles;
    cl_mem          planes;
    cl_mem          textures;
    cl_mem          mats;
    cl_mem          lights;
    t_texture_data  skybox;        // Skybox texture descriptor for GPU
}                   t_scene;
```

The `t_scene` struct includes a `t_vector mesh` for loaded mesh instances, handles planes via the general `objects` vector and `plane_count` (there is no separate `planes_id` field), and uses `t_bvh_engine` - a unified BVH system with a single set of AABB/Sphere BVH pointers.

### `t_bvh_engine` - Unified BVH System

The BVH system state (`t_bvh_engine` and `t_bvh_header`) is documented in [05-bvh.md](05-bvh.md) with full struct definitions, bounding volume shapes, and splitting algorithms.

### `t_params` - Render Parameters

```c
typedef struct s_params
{
    int     *render_mode;   // Pointer to current render mode (0-5)
    int     bvh_depth;      // BVH debug depth
    int     color_offset;   // Color palette offset for heat mode
    bool    bvh_debug;      // Show BVH wireframe overlay
    int     ui_mode;        // UI mode (0=hidden, 1=visible)
    float   exposure;       // Exposure multiplier
}           t_params;
```

Note that `render_mode` is an `int*` - it points to the render mode variable owned by the UI, allowing both the UI and the render loop to share the same value.

### `t_buffers` - Frame Buffers

```c
typedef struct s_buffers
{
    unsigned int    *addr;   // RGBA pixel buffer (for display)
    t_vec3          *accu;   // Accumulation buffer (HDR float3, for progressive rendering)
}                   t_buffers;
```

### `t_opencl` - OpenCL State

The OpenCL state (`t_opencl`) is documented in [06-opencl-integration.md](06-opencl-integration.md) with the full struct definition, initialization flow, and kernel details.

### `t_ui` - UI State

The UI state (`t_ui`) is documented in [10-ui-system.md](10-ui-system.md) with the full struct definition, hierarchy tree, and edit panel architecture.

## Module Dependency Diagram

```mermaid
flowchart TB
    subgraph BINARY["miniRT Binary (src/)"]
        MAIN["main.c"]
        LOOP["loop.c<br/>(render loop dispatch)"]
        PARSING["parsing/<br/>rt_parser, fill_gpu_data"]
        CALC["calc/<br/>BVH, kernels, renderers"]
        INIT["init/<br/>UI setup, graphics init"]
        EXPORT["export_scene/<br/>write .rt files"]
        HOOKS["hooks/<br/>keyboard, mouse, params"]
    end

    subgraph LIBS["Library Submodules (lib/)"]
        LIBFT["libft<br/>vectors, colors,<br/>matrices, utilities"]
        MLX["minilibx-linux<br/>X11 window + image"]
        MLXW["mlx_wrapper<br/>input abstraction,<br/>draw helpers"]
        FONT["font_renderer<br/>TTF parsing +<br/>rasterization"]
        MLXUI["mlxui<br/>GUI component toolkit"]
        XCERRCAL["xcerrcal<br/>structured error<br/>handling"]
    end

    subgraph ASSETS["Assets (minirt-assets/)"]
        SCENES["test .rt files"]
        MESHES["OBJ meshes"]
        MATERIALS["MTL materials"]
        TEXTURES["PPM textures"]
    end

    MAIN --> PARSING
    MAIN --> INIT
    MAIN --> LOOP
    MAIN --> HOOKS
    LOOP --> CALC
    PARSING --> CALC
    CALC --> MLXW
    INIT --> MLXUI
    INIT --> MLXW
    INIT --> FONT
    LOOP --> MLXW

    MLXW --> MLX
    MLXW --> LIBFT
    FONT --> MLXW
    FONT --> MLX
    FONT --> LIBFT
    MLXUI --> FONT
    MLXUI --> MLXW
    MLXUI --> MLX
    MLXUI --> LIBFT
    PARSING --> XCERRCAL
    CALC --> XCERRCAL
    CALC --> LIBFT

    PARSING --> ASSETS
    CALC --> ASSETS

    classDef binary fill:#1a1a2e,stroke:#e94560,color:#fff
    classDef lib fill:#16213e,stroke:#0f3460,color:#fff
    classDef asset fill:#0f3460,stroke:#533483,color:#fff

    class MAIN,LOOP,PARSING,CALC,INIT,EXPORT,HOOKS binary
    class LIBFT,MLX,MLXW,FONT,MLXUI,XCERRCAL lib
    class SCENES,MESHES,MATERIALS,TEXTURES asset
```

## Render Pipeline Flowchart

The render loop dispatch is documented in [06-opencl-integration.md](06-opencl-integration.md) with a detailed frame-by-frame sequence diagram covering kernel dispatch, accumulation, display, UI rendering, and export.

## Data Flow - From `.rt` File to GPU

```mermaid
sequenceDiagram
    participant File as .rt Scene File
    participant Parser as rt_parser
    participant Scene as t_scene (CPU)
    participant Fill as fill_gpu_data
    participant GPU as OpenCL Device
    participant Kernels as Render Kernels

    File->>Parser: parse_scene("scene.rt")
    Note over Parser: Reads line by line

    Parser->>Parser: get_type() -> A, C, L, sp, pl, obj, sky, mtl
    Parser->>Parser: parse_line() per identifier

    alt mtl line
        Parser->>Parser: parse_mtl_file(fd)
        Parser->>Scene: create_mat(&mat, &texture)
        Parser->>Scene: parse texture maps (PPM/PFM)
    else obj line
        Parser->>Parser: parse_obj_file(fd)
        Parser->>Parser: parse faces -> t_triangle objects
        Parser->>Scene: vector_add(&objects, triangle)
        Parser->>Scene: vector_add(&mesh, t_mesh)
    else sp/pl/cy
        Parser->>Scene: create_object(scene, type)
        Parser->>Scene: get_mat(mat_name, &color)
        Parser->>Scene: vector_add(&objects, object)
    end

    Parser->>Scene: fill_by_type()
    Note over Scene: All objects, materials,<br/>textures, lights populated

    Scene->>Fill: fill_gpu_data(state, scene)
    Fill->>Fill: clCreateBuffer for spheres,<br/>triangles, planes,<br/>textures, mats, lights

    Fill->>GPU: clEnqueueWriteBuffer<br/>(copy all GPU buffers)

    Scene->>Fill: create_bvh(&bvh_header, shape, split, objects)
    Fill->>Fill: Evaluate all shape/split combos<br/>(AABB/Sphere/OBB x SAH/MedPrim/MedSpace)
    Fill->>Scene: world_best_bvh selected
    Fill->>GPU: clCreateBuffer + write bvh nodes

    loop Per frame
        Kernels->>GPU: clSetKernelArg(bvh, spheres,<br/>triangles, planes, mats,<br/>lights, camera, textures)
        Kernels->>GPU: clEnqueueNDRangeKernel<br/>(ray generation + traversal)
        GPU->>GPU: hit_bvh_aabb/hit_bvh_obb/hit_bvh_sphere
        GPU->>GPU: shade() <- Phong/PBR/Monte Carlo
        GPU->>GPU: write to output buffer
        GPU->>CPU: clEnqueueReadBuffer(img)
        CPU->>Display: mlx_put_image_to_window()
    end
```

## Submodule Descriptions

### `libft` - Foundation Library

The 42 School standard library, stripped for miniRT. Key components include the **Vectors** module (`t_vec2`, `t_vec3`, `t_vec4` - constructors, arithmetic, dot/cross product, normalization, reflection, rotation), the **Colors** module (`t_rgb` as float, `t_rgb_int` as uint8, conversion routines, `get_real_ratio()` for light scaling), the **Matrices** module (`t_mat3`, `t_mat4` - constructors, multiplication, identity, transpose, Jacobi helper ops), the **Utilities** module (`t_vector` dynamic array, `t_list`, string functions including `ft_scan` - typed scanf with range validation, memory operations, math helpers), and the **File I/O** module (`get_next_line`, file descriptor utilities, PPM loader via `mlx_ppm_to_image`).

### `minilibx-linux` - X11 Graphics

The 42 School's minimal X11/OpenGL wrapper. It provides `t_mlx` for display connection and window management, `t_img_data` as an XImage with pixel buffer access, basic drawing primitives (pixel put, line, rectangle), keyboard and mouse event callbacks, and image creation from PPM files.

### `mlx_wrapper` - Input and Drawing Abstractions

Sitting on top of minilibx, this module provides **input abstraction** (key mapping, key repeat handling, mouse button/position tracking, scroll wheel), **draw helpers** (`mlx_draw_pixel()`, `mlx_draw_line()`, `mlx_draw_rect()`, filled shapes, circle drawing), **image utilities** (image creation, PPM file loading, pixel buffer manipulation), and **event registration** (unified hook setup for keyboard, mouse, expose, and loop hooks).

### `font_renderer` - TrueType Rasterization

This library parses and rasterizes TrueType (.ttf) font files, including TTF table parsing (cmap, glyf, loca, head, hhea, hmtx), glyph outline rasterization (quadratic and cubic Bezier curves), advance width and kerning, a pre-rasterized glyph atlas for performance. It is used by `mlxui` for all text rendering (labels, buttons, values, FPS display).

### `mlxui` - GUI Component Toolkit

A complete immediate-mode GUI toolkit built on `minilibx-linux` + `mlx_wrapper` + `font_renderer`. It uses a **hierarchy tree** (`t_htree` / `t_hbranch`) for component organization, supporting containers (vertical/horizontal layout), Box (spacer, divider), Button (clickable), ButtonGroup (mutually exclusive toggle group), Checkbox (boolean toggle), ColorPicker (RGB color selection with preview), Form (label + value pair), Image (texture display), ScrollBox (scrollable container), Select (dropdown list), Slider (range input), and TextBox (text label). It is used for the scene list, edit panels (geometry, material, camera), render mode switch, FPS overlay, and info display.

### `xcerrcal` - Structured Error Handling

A lightweight error handling framework providing **error codes** (module-specific error IDs), **error packing** (`pack_err()` packs module ID + error ID into an integer), **error reporting** (`error()` with file, line, and function context via macros (`FL`, `LN`, `FC`)), **complex error messages** (`register_complex_err_msg()` for dynamic error context), and **cleanup hooks** (`setup_cleanup_hooks()` for resource cleanup on error).

### `minirt-assets` - Test Scenes and Meshes

A separate repository (submodule at `minirt-assets/`) containing test scenes (`.rt`), OBJ meshes, MTL materials, and PPM textures. See [09-asset-catalog.md](09-asset-catalog.md) for the full asset listing.