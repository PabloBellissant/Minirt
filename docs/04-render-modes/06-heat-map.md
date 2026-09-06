# Heat Map Mode (Index 5)

Heat map mode visualizes the **BVH traversal depth** per pixel as a color-coded heat map, exposing how deeply the BVH is traversed for each ray. This is a debugging tool for BVH performance and balance.

## Source File

`shader/heat.cl`

## Kernel Flow

```
heat() kernel (per pixel)
  ├─ calc_ray(&cam, pos, &rng)
  ├─ hit_depth = hit_bvh_depth(&ray, bvh, bvh_type)
  ├─ if (hit_depth <= 1):  return   (no visible heat for trivial traversals)
  └─ img[pixel] += heatmap(hit_depth / (max_depth²), color_offset)
```

## BVH Depth Counting

Three variants of depth counting exist, one per BVH bound type:

| BVH Type | Function                | Description                          |
|----------|-------------------------|--------------------------------------|
| 0        | `hit_bvh_depth_sphere`  | Sphere BVH traversal depth counting  |
| 1        | `hit_bvh_depth_aabb`    | AABB BVH traversal depth counting    |
| 2        | `hit_bvh_depth_obb`     | OBB BVH traversal depth counting     |

Each function traverses the BVH while counting how many nodes were **entered** (i.e., the ray intersected the node's bounding volume). The traversal uses the standard BVH `skip` pointer pattern:

```c
int hit_bvh_depth_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
    if (bvh[0].children[0] <= 0 && bvh[0].object_id == -1)
        return (-1);          // empty tree
    node = 0;
    hit_count = 0;
    while (node != -1)
    {
        if (bvh[node].children[0] > 0 && hit_sphere(ray, &bvh[node]))
        {
            ++hit_count;      // counted for interior nodes only
            ++node;           // go to first child
        }
        else
            node = bvh[node].skip;   // skip subtree
    }
    return (hit_count);
}
```

The dispatcher selects the variant based on `bvh_type`:

```c
int hit_bvh_depth(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh, int bvh_type)
{
    if (bvh_type == 0) return hit_bvh_depth_sphere(ray, bvh);
    if (bvh_type == 1) return hit_bvh_depth_aabb(ray, bvh);
    return hit_bvh_depth_obb(ray, bvh);
}
```

## Normalization

The raw hit depth is normalized by $\text{max\_depth}^2$:

```c
float v = (float)hit_depth / (max_depth * max_depth);
img[pixel] += heatmap(v, color_offset);
```

The `max_depth` is passed from the CPU side (`data->scene.bvh.world_bvh->max_depth`). Squaring the max depth compresses the heat range, making shallow traversals appear cooler.

## Color Palettes

Ten predefined palettes are available, selected by `color_offset % 10`. Each palette is defined as an array of color stops, linearly interpolated:

| ID | Name                | Stops | Description                              |
|----|----------------------|-------|------------------------------------------|
| 0  | Black → White        | 2     | Grayscale                                |
| 1  | Cool → Warm          | 4     | Dark blue → cyan → yellow → red          |
| 2  | Dark → Gold          | 4     | Black → purple → orange → gold           |
| 3  | Violet → Teal → Yellow | 3   | Deep purple → teal → bright yellow        |
| 4  | Magenta → Pink → Gold | 3   | Purple → pink → yellow                    |
| 5  | Black → Red → Gold   | 3     | Black → dark red → bright yellow         |
| 6  | Deep Blue → Cyan → White | 3 | Navy → cyan → near-white                 |
| 7  | Black → Red → Orange → White | 4 | Black → deep red → orange → white |
| 8  | Black → Green → Lime  | 3     | Black → dark green → bright green        |
| 9  | Dark Gray → Light Gray | 2    | Subtle grayscale                         |

The palette system is implemented as:

```c
typedef struct s_palette
{
    int     color_count;     // number of color stops
    float3  color[4];        // up to 4 stops
} t_palette;

float3 heatmap(float v, int color_id)
{
    v = clamp(v, 0.0f, 1.0f);
    color_id %= 10;
    t_palette p = get_palette(color_id);

    if (p.color_count <= 1)
        return p.color[0];

    float scaled = v * (p.color_count - 1);
    int idx = (int)scaled;
    float t = scaled - idx;
    idx = clamp(idx, 0, p.color_count - 2);

    return p.color[idx] + t * (p.color[idx + 1] - p.color[idx]);
}
```

The interpolation is **linear** between color stops (RGB lerp).

## Color Offset

The heat map uses `data->params.color_offset` (modulo 10) to select the active palette. Changing this parameter lets the user cycle through palettes interactively.

## BVH Type Variants

The heat map respects the scene's BVH type. If the BVH was built with spheres (`BVH_SPHERE`), the `hit_bvh_depth_sphere` path is used; if AABB, `hit_bvh_depth_aabb`; if OBB, `hit_bvh_depth_obb`. This means the heat map adapts to whatever BVH shape is active, and the traversal cost distribution varies accordingly.

## Usage

- Pixels with hit_depth $\leq 1$ (no or trivial traversal) are left black (no contribution).
- Deep traversals (many nodes visited) appear progressively "hotter" according to the selected palette.
- Cold regions = rays that hit early (shallow traversal, good BVH).
- Hot regions = rays that penetrated deeply (many BVH nodes visited, possibly poor spatial partitioning).