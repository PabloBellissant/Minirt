# Render Modes — Overview

MiniRT provides **6 render modes** for visualizing the scene. One mode
(wireframe) runs on the CPU; the other five are GPU-accelerated OpenCL kernels.
The active mode is selected via keyboard shortcuts and routed through a
dispatch table.

---

## 1. Mode Summary

| Index | Mode | Key | Architecture | Purpose |
|---|---|---|---|---|
| 0 | Wireframe | `1` | CPU | Debug rasterization: BVH boxes, object outlines, light positions |
| 1 | Phong | `2` | GPU | Standard Phong shading: ambient + diffuse + specular + emissive |
| 2 | PBR | `3` | GPU | Physically based rendering: Fresnel, reflectivity, refraction, bounces |
| 3 | Monte Carlo | `4` | GPU | Path tracing with GGX microfacet sampling and chromatic dispersion |
| 4 | Normal | `-` (minus) | GPU | Normal-to-color debug: visualize surface normals |
| 5 | Heat | `=` (equals) | GPU | BVH traversal depth heat map |

---

## 2. Dispatch Table

The dispatch table is defined in `src/loop.c`:

```c
static void (*render_func[])(t_data *, t_img_data *img)
    = {wireframe_render, phong_render, pbr_render,
       monte_carlo_render, normal_render, heat_render};
```

Each function in the table has the same signature:

```c
void render_mode(t_data *data, t_img_data *img);
```

The active mode is stored in `data->params.render_mode` (0–5). The main loop
calls `render_func[data->params.render_mode](data, img)` every frame.

---

## 3. Keyboard Switching

Keys `1`–`4` switch to Wireframe, Phong, PBR, and Monte Carlo modes
respectively. Keys `-` and `=` toggle between Normal debug and Heat map modes.

For the full keybinding table including camera movement, BVH debug, and
special controls, see [07-camera-and-interaction.md](../07-camera-and-interaction.md).

---

## 4. Progressive Accumulation / Rendering Pattern

All GPU render modes share a common progressive rendering pattern. The
accumulation buffer (`data->buffers.accu`, a `float3` array of size
`WIDTH × HEIGHT`) persists across frames, averaging new samples with
previous ones. The frame counter resets when the camera moves, mode
changes, or any render parameter changes.

After N frames, each pixel has N samples and noise is reduced by √N:

```
Frame 1:   1 sample/pixel — very noisy
Frame 100: 100 samples/pixel — smooth
```

For the full accumulation buffer architecture, per-frame flow, reset
triggers, and GPU host-to-device transfer details, see
[06-opencl-integration.md](../06-opencl-integration.md).

---

## 5. Mode Comparison

| Mode | Speed | Quality | Use Case |
|---|---|---|---|
| Wireframe | Instant | Debug only | Understanding scene topology, BVH structure |
| Phong | Very fast | Basic, no shadows | Quick preview, low-spec hardware |
| PBR | Fast | Good, with reflections | Scene preview with physically based lighting |
| Monte Carlo | Slow (~1 frame/sample) | Best, path traced | Final render quality with realistic light transport |
| Normal debug | Very fast | Debug only | Checking normal map correctness |
| Heat map | Very fast | Debug only | BVH traversal efficiency analysis |

---

## 6. Common Implementation Details

All GPU modes share these OpenCL pipeline elements:

- **Kernel source** is embedded in the binary as a single C string literal
  that `#include`s all `.cl` files
- **Work-item mapping**: each work-item handles exactly one pixel
- **Camera struct** (`t_camera_gpu`) is passed as a kernel argument
- **BVH buffers** are uploaded via `clCreateBuffer(CL_MEM_COPY_HOST_PTR)`
- **Texture sampling** uses the `sample_texture.cl` library with bilinear
  interpolation
- **Random numbers** use the `random.cl` PRNG (per-pixel state)