# Render Mode: Heat Map (Mode 5)

Heat map mode visualizes the **BVH traversal depth** per pixel — how many BVH
node intersection tests were performed before finding the nearest primitive.
This is a diagnostic mode for understanding BVH traversal efficiency and
identifying poorly partitioned regions.

---

## 1. Concept

During BVH traversal, each ray visits a sequence of nodes. The kernel counts:

$$\text{hit\_depth} = \text{number of BVH nodes tested}$$

This depth is normalized and mapped through a color palette to produce a heat
map:

- **Blue/purple** regions = few BVH nodes tested (efficient traversal)
- **Red/white** regions = many BVH nodes tested (inefficient traversal)

---

## 2. Normalization

The raw hit depth is normalized by the square of the maximum BVH depth:

$$\text{value} = \frac{\text{hit\_depth}}{\text{max\_depth}^2}$$

where $\text{max\_depth}$ is the deepest node in the BVH tree.

Using $\text{max\_depth}^2$ in the denominator compresses the value range,
making differences in shallow traversal more visible while preventing deep
traversal from saturating the palette.

The result $\text{value} \in [0, 1]$ is passed to the color palette
interpolation.

---

## 3. Color Palettes

The heat map supports **10 color palettes**, each defined by 2–4 gradient
stops. The user can cycle through palettes using `bvh_color_offset`.

### 3.1. Palette Definitions

| Palette Index | Stops | Description |
|---|---|---|
| 0 | Blue → Cyan → Green → Yellow → Red | **Classic heat map** (cold → hot) |
| 1 | Black → Blue → Magenta → White | **Inferno-like** (dark → bright) |
| 2 | Black → Red → Yellow → White | **Ironbow** (black body radiation) |
| 3 | Blue → Green → Yellow → Red | **Jet** (MATLAB-like) |
| 4 | Black → Purple → Orange → Yellow | **Plasma** |
| 5 | Black → Blue → Cyan → White | **Cool** (blue-dominant) |
| 6 | Green → Yellow → Red | **Traffic light** |
| 7 | Blue → White | **Simple blue-white** |
| 8 | White → Yellow → Red → Black | **Inverted classic** |
| 9 | Black → White | **Grayscale** |

### 3.2. Palette Interpolation

Each palette is defined as an array of $(t_i, C_i)$ stop pairs where $t_i$ is
the normalized position and $C_i$ is the RGB color.

For a given $\text{value} \in [0, 1]$, the output color is computed by finding
the two nearest stops and **linear interpolation**:

$$i = \max\{j \mid t_j \leq \text{value}\}$$
$$f = \frac{\text{value} - t_i}{t_{i+1} - t_i}$$
$$C = (1 - f) \cdot C_i + f \cdot C_{i+1}$$

This produces smooth color gradients across the palette.

---

## 4. Kernel Flow

```
heat_kernel(pixel_x, pixel_y):
    1. Generate camera ray
    2. Initialize hit_depth = 0

    3. Traverse BVH (BVH2 stackless or BVH4/8 stack-based):
       - For each visited node:
           hit_depth++
           If ray hits node AABB:
               If leaf: test primitives
               Else: continue traversal
           Else: skip (using skip pointer or stack pop)

    4. If no hit → return background / skybox color

    5. Normalize:
       value = hit_depth / (max_depth * max_depth)
       value = clamp(value, 0, 1)

    6. Look up palette:
       palette_idx = active_palette (from bvh_color_offset)
       color = heatmap(value, palette_idx)

    7. accu[pixel] += color
```

---

## 5. Interpretation

| Heat Color | BVH Traversal | Interpretation |
|---|---|---|
| Dark blue / black | Very few nodes | Ray traverses directly to the surface — spatially coherent |
| Green / yellow | Moderate nodes | Some backtracking or wide nodes — reasonable efficiency |
| Red / white | Many nodes | Poor spatial partitioning — possibly overlapping primitives or deep BVH |

### 5.1. Common Patterns

- **Red streaks at object edges**: Rays grazing surfaces at oblique angles
  traverse many neighboring BVH nodes due to overlapping AABBs
- **Uniform blue on flat regions**: Rays hitting large surfaces directly with
  minimal BVH descent
- **Red regions in complex geometry**: High-poly OBJ meshes with deep BVH trees
  produce more node tests
- **Red sky**: Rays that miss all geometry terminate after traversing the full
  BVH tree — the deepest possible traversal

---

## 6. Use Cases

- **BVH quality assessment**: Compare sphere BVH vs. SAH AABB BVH traversal
  depths side by side
- **Scene complexity analysis**: Identify regions where geometry is
  concentrated
- **BVH2 vs BVH4 vs BVH8 comparison**: Wider nodes (BVH8) should reduce
  traversal depth at the cost of more node tests per level
- **Debugging BVH construction errors**: Unexpected red patches may indicate
  incorrect SAH binning or split plane selection

---

## 7. Performance

Heat map mode is slightly slower than normal debug mode because it counts BVH
node visits during traversal, but it still requires only:

- 1 primary ray cast
- 1 BVH traversal (with counter increment per node)
- 1 palette lookup and interpolation

Performance is close to Phong mode speed.