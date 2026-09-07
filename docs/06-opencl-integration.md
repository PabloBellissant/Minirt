# OpenCL Integration

## Overview

miniRT uses OpenCL for all GPU-accelerated ray tracing. The host (C code) manages the OpenCL lifecycle (platform enumeration, device selection, kernel compilation, buffer management, and dispatch) while the device (OpenCL C kernels) executes the actual intersection and shading computations. The rendering pipeline is designed for progressive accumulation (see [Accumulation Buffer Architecture](#accumulation-buffer-architecture)).

The OpenCL state bundles a platform, device, context, command queue, program, six kernel objects, GPU buffers (accumulation and output image), and a host-side readback buffer for display output.

*Diagram showing the relationship between the host (C code), OpenCL platform layer, and GPU device with kernels.*

---

## Initialization Flow

```mermaid
graph TD
    A["init_opencl(state, CL_DEVICE_TYPE_GPU)"] --> B["clGetPlatformIDs<br/>enumerate up to 8 platforms"]
    B --> C{"clGetDeviceIDs<br/>GPU on this platform?"}
    C -->|"No"| D["try next platform"]
    C -->|"Yes"| E["init_gpu(state)"]
    E --> F["clCreateContext<br/>with GPU device"]
    F --> G["clCreateCommandQueueWithProperties<br/>in-order queue"]
    G --> H["clCreateProgramWithSource<br/>KERNEL_SOURCE"]
    H --> I["clBuildProgram<br/>-Ishader -cl-fast-relaxed-math -cl-mad-enable"]
    I -->|"FAIL"| J["print build log to stderr<br/>cleanup, return -1"]
    I -->|"OK"| K["create_kernels(state)"]
    K --> L["clCreateKernel x 6<br/>monte_carlo, normal_debug, phong<br/>draw_accu, pbr, heat"]
    L --> M["clCreateBuffer: accu<br/>CL_MEM_READ_WRITE<br/>float3 x WIDTH x HEIGHT"]
    M --> N["clCreateBuffer: img<br/>CL_MEM_READ_WRITE<br/>int x WIDTH x HEIGHT"]
    N --> O["allocate host_buffer"]
    O --> P["Ready"]
```

The initialization proceeds through several stages. First, **platform enumeration** uses `clGetPlatformIDs()` to find up to 8 OpenCL platforms, iterating until a platform provides a device matching `CL_DEVICE_TYPE_GPU`. Next, **device selection** calls `clGetDeviceIDs()` on each platform; the first platform with a matching device wins. Then **context and queue** creation uses `clCreateContext()` and `clCreateCommandQueueWithProperties()` with an in-order queue (kernels execute sequentially per frame). **Program compilation** calls `clBuildProgram()` with the embedded kernel source string and flags `-Ishader -cl-fast-relaxed-math -cl-mad-enable`; on failure the build log is retrieved via `clGetProgramBuildInfo()` and printed to stderr. **Kernel creation** calls `clCreateKernel()` for each of 6 kernels. Finally, **buffer allocation** creates the accumulation buffer (`float3 x WIDTH x HEIGHT`) and output image buffer (`int x WIDTH x HEIGHT`) as read-write GPU buffers.

---

## Kernel Source Embedding

All OpenCL kernel source is compiled into the binary as a single C string literal. Each `.cl` file in the shader directory is included via the OpenCL `#include` mechanism (resolved relative to the `-I` include path), producing one compilation unit where cross-file function calls are resolved at compile time. This eliminates file I/O at runtime and avoids shipping external `.cl` files alongside the binary, at the cost of increased binary size. Shared type definitions (`t_camera_gpu`, `t_ray_gpu`, `t_objects`, `t_mat_gpu`, `t_hit_gpu`, `t_hit_data`, etc.) live in a common header included by all kernel files.

---

## The 6 Kernels

### 1. `phong` - Phong Shading

For each pixel, casts one ray, finds the nearest hit via BVH, samples materials (textures + normal maps), and computes Phong shading (ambient + diffuse + specular + emissive) against all lights. Single-bounce shading.

### 2. `pbr` - Physically Based Rendering

Multi-bounce ray tracing (up to `MAX_BOUNCE` = 4) with Fresnel reflection/refraction via `sample_refract()`, Schlick approximation, and roughness-based Cook-Torrance glossy factor. Accumulates color through reflected rays with `through_power` attenuation. Supports refractive materials with Snell's law.

### 3. `monte_carlo` - Monte Carlo Path Tracing

Full path tracing with GGX/Trowbridge-Reitz microfacet importance sampling (`sample_ggx_gpu`), chromatic dispersion (wavelength-dependent IOR via `get_ni_by_color`), emissive surfaces, and rainbow-colored refractions (`rainbow_color`). Each frame accumulates into the buffer for progressive denoising, up to `MAX_BOUNCE` (4) bounces.

### 4. `normal_debug` - Normal Visualization

Maps the shading normal to RGB: `img[pixel] = hit_data.normal * 0.5 + 0.5`. Normal maps are applied before visualization, so perturbed normals are visible.

### 5. `heat` - BVH Traversal Depth Heat Map

Traverses the BVH counting the number of inner nodes intersected (stackless traversal with skip pointers). Maps the count to a color from one of 10 built-in palettes (2-4 gradient stops). The palette is cycled via the `C` key (which increments `color_offset`).

### 6. `draw_accu` - Accumulation Buffer to Image

Divides each pixel's accumulated `float3` color by `max(1.0f, sample_count)`, multiplies by 255, clamps to [0, 255], and packs into a 32-bit integer for minilibx display.

---

## NDRange Dispatch

Every kernel is dispatched with a 2D global work size equal to the screen dimensions. Each work item processes exactly one pixel, computing its position from `get_global_id(0)` and `get_global_id(1)`. The local work size is `NULL`, allowing OpenCL to pick it automatically based on device capabilities. No explicit work-group sizing is used.

---

## Accumulation Buffer Architecture

The project uses a two-buffer progressive accumulation scheme on the GPU. The **accu** buffer (`float3[]`, WIDTH x HEIGHT, `CL_MEM_READ_WRITE`) stores accumulated samples, while the **img** buffer (`int[]`, WIDTH x HEIGHT, `CL_MEM_READ_WRITE`) holds the normalized display output. On the host side, a **host_buffer** (`int[]`, WIDTH x HEIGHT) receives the GPU output and is copied into the minilibx image object via `mlx_put_data_addr` and `mlx_put_image_to_window`.

*Diagram showing how render kernels write to the accumulation buffer, which is normalized by draw_accu and read back to the host for display.*

### Flow per Frame

If the camera position, rotation, FOV, lens radius, or focus distance changed (`cam_has_moved()`), or if render parameters changed (`render_changed()`), the accumulation buffer is **zeroed out** (via `clEnqueueWriteBuffer` with zeros) and `camera.frame` is reset to 1. Then `camera.frame` increments and one of 5 GPU kernels runs, writing `float3` values into the accumulation buffer. The `draw_accu` kernel divides each pixel's accumulated value by `max(1.0f, frame x exposure)`, multiplies by 255, clamps, and writes to `img`. The `img` buffer is read back to the host via `clEnqueueReadBuffer`. The host buffer is copied into the minilibx image and displayed via `mlx_put_data_addr` and `mlx_put_image_to_window`.

The result is progressive rendering with exposure control. After N frames, each pixel has N samples and noise is reduced by sqrt(N). **Exposure** (adjusted via F5/F6, see [07-camera-and-interaction.md](07-camera-and-interaction.md)) acts as a multiplier on the sample count divisor.

---

## Host-to-GPU Data Transfer

Scene data is transferred to the GPU during scene loading via `clCreateBuffer` with `CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR`, which allocates GPU memory and copies the host data in a single call. The data categories transferred include BVH nodes (once on BVH build), sphere/triangle/plane arrays (once on scene load), the texture atlas (once on scene load), material arrays (once on scene load), and light arrays (once on scene load). All buffers use `CL_MEM_READ_ONLY` except the accumulation and image buffers which use `CL_MEM_READ_WRITE`.

The texture atlas (a flat byte array of all concatenated textures) is documented in [08-materials-and-textures.md](08-materials-and-textures.md) with per-pixel sampling details.

---

## Render Frame Sequence

The main loop executes the following sequence every frame:

```mermaid
sequenceDiagram
    participant Main as "C Main Loop"
    participant Cam as "Camera Module"
    participant GPU as "GPU<br/>(OpenCL Device)"
    participant HostBuf as "Host Buffer"
    participant Display as "minilibx Window"
    participant UI as "UI System"

    Main->>Cam: handle_camera_move()
    Main->>Cam: cam_has_moved()?
    Cam-->>Main: yes / no

    alt camera moved or render params changed
        Main->>GPU: clEnqueueWriteBuffer(accu, zeros)
        Main->>Cam: reset frame counter to 1
    end

    Main->>Cam: increment frame counter
    Main->>GPU: clSetKernelArg (camera, bvh, spheres, ...)
    Main->>GPU: clEnqueueNDRangeKernel(render_func[*mode])
    Note over GPU: Each work-item -> one pixel<br/>Intersect -> shade -> accumulate float3

    Main->>GPU: clEnqueueNDRangeKernel(draw_accu)
    Note over GPU: accu[pixel] / max(1, frame x exposure) -> packed RGB int

    Main->>GPU: clEnqueueReadBuffer(img -> host_buffer)
    Main->>Display: mlx_put_data_addr
    Main->>Display: mlx_put_image_to_window

    alt selection not empty
        Main->>Display: rasterize_selected (highlight selected objects)
    end

    alt export_render_task flag is set
        Main->>UI: hide UI (ui_toggle = false)
        Main->>Display: export_to_ppm (PPM screenshot, hidden UI)
        Main->>UI: restore UI (ui_toggle = true)
        Main->>UI: clear export_render_task flag
    end

    Main->>UI: update_fps (FPS counter string)

    alt mouse is dragging (selection zone)
        Main->>Display: draw_select (selection box overlay)
    end

    alt ui_mode != 2 (hidden)
        Main->>Display: render_hierarchy (full UI tree)
    end

    alt bvh_debug enabled
        Main->>Display: debug_rasterize_bvh (CPU wireframe overlay)
    end
```

### Cumulative Rendering

The accumulation buffer is never cleared unless camera or render state changes, providing instant feedback on camera movement while gradually converging to a noise-free image when stationary.