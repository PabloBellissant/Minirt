# Render Modes — Overview

miniRT supports **6 render modes**, selected at runtime and switched interactively via keyboard. Each mode produces a different visual output depending on the rendering technique used.

## Mode Dispatch

The render loop in `src/loop.c` maintains a static function pointer table:

```c
static int (*render_func[])(t_data *, t_img_data *img)
    = {wireframe_render, phong_render, pbr_render,
       monte_carlo_render, normal_render, heat_render};
```

The current mode is read from `*data->params.render_mode` (an `int` pointer). The dispatch call is:

```c
if (render_func[*data->params.render_mode](data, &data->mlx->img) != 0)
    // error — break mlx loop
```

Each render function returns `int` (0 on success, non-zero to signal exit).

## Mode Table

| Index | Mode          | Description                              | Type             |
|-------|---------------|------------------------------------------|------------------|
| 0     | Wireframe     | CPU rasterization, BVH debug overlay     | CPU (raster)     |
| 1     | Phong         | Per-pixel Phong shading with shadow rays | GPU (OpenCL)     |
| 2     | PBR           | Physically-based rendering, multi-bounce | GPU (OpenCL)     |
| 3     | Monte Carlo   | Path tracing, GGX sampling, dispersion   | GPU (OpenCL)     |
| 4     | Normal Debug  | Surface normal visualization             | GPU (OpenCL)     |
| 5     | Heat Map      | BVH traversal depth visualization        | GPU (OpenCL)     |

## Keyboard Switching

The user switches render modes via keyboard input. Mode 0–5 are cycled or directly selected. The `*data->params.render_mode` value is updated, which triggers `render_changed()` to reset the progressive accumulation buffer.

## Progressive Accumulation

All GPU modes (Phong, PBR, Monte Carlo, Normal, Heat) use **progressive accumulation**:

- A `float3 *accu` buffer accumulates samples per pixel across frames.
- A `frame` counter in the camera struct increments each frame.
- On each frame the kernel is dispatched with `cam.frame` as a seed component.
- After the kernel, `draw_accu` divides the accumulated buffer by the sample count and writes to the display image.
- **Reset condition**: When `cam_has_moved()` or `render_changed()` returns true, the accumulation buffer is cleared and `cam.frame` is reset to 1.

The accumulation kernel (`shader/draw_accu.cl`):

```c
__kernel void draw_accu(__global float3 *accu, __global int *img, int sample_count)
{
    // ...
    accu_divide = (accu[pixel] / (max(1.0f, (float) sample_count))) * 255.0f;
    accu_divide = clamp(accu_divide, 0, 255);
    color.r = accu_divide[0];
    color.g = accu_divide[1];
    color.b = accu_divide[2];
    img[pixel] = color.rgb;
}
```

### Per-Mode Accumulation Pattern

| Mode        | Accumulates | Frame Reset Triggers              |
|-------------|-------------|-----------------------------------|
| Phong       | `img[pixel] += hit_data.kd`     | Camera move, param change |
| PBR         | `img[pixel] += accumulated_color` | Camera move, param change |
| Monte Carlo | `img[pixel] += final_color / ...` | Camera move, param change |
| Normal      | `img[pixel] += hit_data.normal * 0.5f + 0.5f` | Camera move, param change |
| Heat        | `img[pixel] += heatmap(...)`      | Camera move, param change |