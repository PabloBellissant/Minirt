# Heat Map Mode (Index 5)

Heat map mode visualizes the **BVH traversal depth** per pixel as a color-coded heat map, exposing how deeply the BVH is traversed for each ray. This is a debugging tool for BVH performance and balance.

## Source File

`shader/heat.cl`

## Kernel Flow

```
heat() kernel (per pixel)
  +-- calc_ray(&cam, pos, &rng)
  +-- hit_depth = hit_bvh_depth(&ray, bvh, bvh_type)
  +-- if (hit_depth <= 1):  return   (no visible heat for trivial traversals)
  +-- img[pixel] += heatmap(hit_depth / (max_depth^2), color_offset)
```

## BVH Depth Counting

Three variants of depth counting exist, one per BVH bound type: `hit_bvh_depth_sphere` for sphere BVH, `hit_bvh_depth_aabb` for AABB BVH, and `hit_bvh_depth_obb` for OBB BVH. Each function traverses the BVH while counting how many nodes were **entered** (i.e., the ray intersected the node's bounding volume). The traversal uses the standard BVH `skip` pointer pattern, counting hits for interior nodes only and skipping leaf/empty nodes. The dispatcher selects the variant based on `bvh_type` (0 = sphere, 1 = AABB, 2 = OBB).

<table>
  <tr>
    <td><img src="docs/assets/img/bvh-volume-theme3.png" alt="BVH heat map theme 3" width="100%"/></td>
    <td><img src="docs/assets/img/bvh-volume-theme4.png" alt="BVH heat map theme 4" width="100%"/></td>
  </tr>
  <tr>
    <td colspan="2" style="text-align:center"><em>Heat map visualization of BVH traversal depth - BVH themes showing traversal depth color-coded across different palette mappings.</em></td>
  </tr>
</table>

## Normalization

The raw hit depth is normalized by $\text{max_depth}^2$: `float v = (float)hit_depth / (max_depth * max_depth)`. The `max_depth` is passed from the CPU side (`data->scene.bvh.world_bvh->max_depth`). Squaring the max depth compresses the heat range, making shallow traversals appear cooler.

## Color Palettes

Ten predefined palettes are available, selected by `color_offset % 10`. Each palette is defined as an array of color stops that are linearly interpolated (RGB lerp):

| ID | Name | Stops | Description |
|---|---|---|---|
| 0 | Black -> White | 2 | Grayscale |
| 1 | Cool -> Warm | 4 | Dark blue -> cyan -> yellow -> red |
| 2 | Dark -> Gold | 4 | Black -> purple -> orange -> gold |
| 3 | Violet -> Teal -> Yellow | 3 | Deep purple -> teal -> bright yellow |
| 4 | Magenta -> Pink -> Gold | 3 | Purple -> pink -> yellow |
| 5 | Black -> Red -> Gold | 3 | Black -> dark red -> bright yellow |
| 6 | Deep Blue -> Cyan -> White | 3 | Navy -> cyan -> near-white |
| 7 | Black -> Red -> Orange -> White | 4 | Black -> deep red -> orange -> white |
| 8 | Black -> Green -> Lime | 3 | Black -> dark green -> bright green |
| 9 | Dark Gray -> Light Gray | 2 | Subtle grayscale |

The palette system is implemented as a struct with up to 4 color stops, and the `heatmap()` function clamps the input value to [0,1], selects the palette, finds the appropriate segment, and performs linear interpolation between the two nearest stops.

## Color Offset

The `data->params.color_offset` parameter (modulo 10) selects the active palette. The `C` key increments `color_offset` each time it is pressed, allowing the user to cycle through palettes interactively in real time.

## BVH Type Variants

The heat map respects the scene's BVH type. If the BVH was built with spheres (`BVH_SPHERE`), the `hit_bvh_depth_sphere` path is used; if AABB, `hit_bvh_depth_aabb`; if OBB, `hit_bvh_depth_obb`. This means the heat map adapts to whatever BVH shape is active, and the traversal cost distribution varies accordingly.

## Usage

Pixels with hit_depth $\leq 1$ (no or trivial traversal) are left black with no contribution. Deep traversals (many nodes visited) appear progressively "hotter" according to the selected palette. Cold regions indicate rays that hit early (shallow traversal, good BVH), while hot regions indicate rays that penetrated deeply (many BVH nodes visited, possibly poor spatial partitioning).