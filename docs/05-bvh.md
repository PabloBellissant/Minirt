# BVH System

The **Bounding Volume Hierarchy (BVH)** accelerates ray-scene intersection by organizing primitives in a spatial tree. Each node stores a bounding volume that encloses all primitives in its subtree. During traversal, nodes whose bounding volume is missed by the ray are skipped, yielding $O(\log n)$ average intersection time.

## Architecture Overview

```mermaid
flowchart TD
    subgraph CPU ["CPU — Scene Setup"]
        SCE[Scene Objects] --> CLEAN[clean_prim\n filter spheres & triangles]
        CLEAN --> CREATE[create_bvh\n select shape + splitting]
        CREATE --> INDEX[index_bvh\n compute skip pointers]
        INDEX --> DEBUG[debug_bvh_tree\n print tree + stats]
        INDEX --> GPU_UPLOAD[Upload to GPU\n clCreateBuffer]
    end

    subgraph GPU ["GPU — Ray Tracing"]
        RAY[Primary Ray] --> TRAVERSE[BVH Traversal\n hit_bvh_{sphere,aabb,obb}]
        TRAVERSE --> HIT{Node hit?}
        HIT -->|Yes| IS_LEAF{Is leaf?}
        IS_LEAF -->|Yes| INTERSECT[Intersect primitive\n triangle / sphere]
        IS_LEAF -->|No| GO_CHILD[++node → first child]
        HIT -->|No| SKIP[node = skip]
        SKIP --> TRAVERSE
        INTERSECT --> NEXT[nearest = min(t)\n node = skip]
        NEXT --> TRAVERSE
        GO_CHILD --> TRAVERSE
    end
```

## Core Structures

### `t_bvh_engine`

The top-level BVH container in `t_scene`. Defined in `include/bvh/bvh.h`:

```c
typedef struct s_bvh_engine
{
    t_bvh_header    *world_best_bvh;  // best BVH from comparison
    t_bvh_header    *world_bvh;       // primary world BVH
    cl_mem          bvh_gpu;          // OpenCL buffer on GPU
} t_bvh_engine;
```

- `world_bvh` — the active world BVH header.
- `world_best_bvh` — a reference to a "best" BVH (for comparison/testing).
- `bvh_gpu` — the OpenCL memory buffer holding the GPU-compact array of `t_bvh_node_gpu`.

### `t_bvh_header`

Metadata for a single BVH tree:

```c
typedef struct s_bvh_header
{
    t_vector        nodes;           // dynamic array of t_bvh_node
    int             max_depth;       // maximum tree depth
    t_bvh_shape     shape;           // BVH_SPHERE, BVH_AABB, or BVH_OBB
    t_bvh_split     splitting_algo;  // SAH, MED_PRIM, or MED_SPACE
    size_t          build_time;      // construction time in microseconds
} t_bvh_header;
```

### `t_bvh_node`

A single node in the BVH tree (binary, arity = 2):

```c
typedef struct s_bvh_node
{
    union {
        int children[2];           // indices of child nodes (interior node)
        struct {
            int _pad[1];           // BVH_ARITY - 1 padding
            int object_id;         // primitives index (leaf node)
            int type;              // SPHERE or TRIANGLE (leaf node)
        };
    };
    int             skip;          // next node to visit after subtree
    t_bvh_bounds    bounds;        // bounding volume
} t_bvh_node;
```

**Interior node**: `children[0]` and `children[1]` are positive indices into the nodes array.

**Leaf node**: `children[0] <= 0`, `object_id` indexes the primitive, `type` identifies the primitive type.

**Skip pointer**: After processing a node, traversal jumps to `skip` instead of returning to parent. This is the "roped BVH" pattern — a flat-array alternative to recursion.

### `t_bvh_bounds`

A **union** of the three bounding volume shapes:

```c
typedef union u_bvh_bounds
{
    t_bvh_sphere  sphere;
    t_bvh_aabb    aabb;
    t_bvh_obb     obb;
} t_bvh_bounds;
```

Only one shape is active per BVH tree, determined by `bvh_header->shape`.

## Bounding Volume Shapes

### 1. AABB — Axis-Aligned Bounding Box

```c
typedef struct s_bvh_aabb
{
    union {
        struct { t_vec3 min; t_vec3 max; };
        t_cuboid cuboid;
    };
} t_bvh_aabb;
```

- Defined by `min` and `max` corners.
- Evaluated by finding the extent of all primitive centroids/vertices in each axis.
- Fastest GPU intersection test (slab method, no rotation transform).
- Good for axis-aligned scenes but wasteful for rotated geometry.

### 2. Sphere Bounding Volume

```c
typedef struct s_bvh_sphere
{
    union { t_vec3 pos; t_vec3 centroid; };
    union { float r; float radius; };
} t_bvh_sphere;
```

- Defined by a center position and a radius.
- Evaluated by computing the centroid of all primitives, then finding the maximum distance.
- Simplest intersection test (point-in-sphere distance).
- Tends to produce more overlap between sibling nodes, reducing BVH efficiency.

### 3. OBB — Oriented Bounding Box

```c
typedef struct s_bvh_obb
{
    t_vec3  center;
    t_vec4  q;              // rotation quaternion
    t_vec3  half_extents;   // half-size along each axis
    t_vec3  axes[3];        // pre-computed basis axes from quaternion
} t_bvh_obb;
```

- Tightest-fitting box for arbitrarily oriented geometry.
- Uses **PCA (Principal Component Analysis)** to find the dominant orientation.

#### OBB Construction Pipeline

The OBB is built through a multi-step pipeline:

```mermaid
flowchart LR
    subgraph PCA ["PCA Computation"]
        MEAN[get_pca_mean\n centroid of all vertices] --> COV[get_pca_covariance\n 3×3 covariance matrix]
        COV --> JACOBI[mat3_eigh_jacobi\n Jacobi eigenvalue decomposition]
    end

    subgraph Basis ["Basis Extraction"]
        JACOBI --> SORT[sort3_desc\n sort eigenvalues descending]
        SORT --> BASIS[basis3_from_eigh\n orthogonalize basis via cross product]
    end

    subgraph Quaternion ["Quaternion Encoding"]
        BASIS --> QUAT[quat_from_mat3_cols\n convert rotation matrix → quaternion]
        QUAT --> AXES[obb_axes_from_quat\n compute axes[0..2] from quaternion]
    end

    subgraph Extents ["Extent Computation"]
        AXES --> PROJECT[mat3_project_objects\n project vertices onto basis]
        PROJECT --> EXTENTS[min/max → half_extents]
    end
```

**Step 1: PCA Mean** (`get_pca_mean`)

The mean position of all primitive vertices is computed:

$$
\bar{\mathbf{p}} = \frac{1}{N} \sum_{i=1}^{N} \mathbf{p}_i
$$

For triangles, each of the three vertices contributes $\frac{1}{3N}$ to the sum.

**Step 2: PCA Covariance** (`get_pca_covariance`)

The $3 \times 3$ covariance matrix is computed from the centered data:

$$
\mathbf{C} = \frac{1}{N} \sum_{i=1}^{N} (\mathbf{p}_i - \bar{\mathbf{p}})(\mathbf{p}_i - \bar{\mathbf{p}})^{\mathsf{T}}
$$

Resulting in a symmetric matrix:

$$
\mathbf{C} = \begin{pmatrix}
C_{xx} & C_{xy} & C_{xz} \\
C_{xy} & C_{yy} & C_{yz} \\
C_{xz} & C_{yz} & C_{zz}
\end{pmatrix}
$$

**Step 3: Jacobi Eigenvalue Decomposition** (`mat3_eigh_jacobi`)

The Jacobi iterative method diagonalizes $\mathbf{C}$ via successive Givens rotations:

```c
void mat3_eigh_jacobi(t_mat3 a, float evals[3], t_mat3 *evecs)
{
    m = a;
    *evecs = mat3_identity();
    for (i = 0; i < EIGH_MAX_ROT; i++)  // max 45 iterations
    {
        r = get_mat3_jacobi_rot_params(m);
        if (r.amax < EIGH_TOL) break;   // EIGH_TOL = 1.0e-9
        mat3_jacobi_apply(&m, evecs, r);
    }
    evals[0] = m.m[0][0];
    evals[1] = m.m[1][1];
    evals[2] = m.m[2][2];
}
```

The diagonalized matrix's diagonal entries are the eigenvalues $\lambda_0, \lambda_1, \lambda_2$. The accumulated rotation matrix is the eigenvector matrix $\mathbf{E}$.

**Step 4: Basis Sorting** (`basis3_from_eigh`)

The eigenvalues are sorted descending, and the corresponding eigenvectors are taken as the new basis axes. A Gram-Schmidt-like orthogonalization via cross products ensures a right-handed orthonormal basis:

```c
sort3_desc(evals, idx);
u = normalize(mat3_get_col(evecs, idx[0]));  // dominant axis
v = normalize(mat3_get_col(evecs, idx[1]));  // second axis
w = normalize(cross(u, v));                   // third = cross(u, v)
v = normalize(cross(w, u));                  // re-orthogonalize v
return mat3_from_cols(u, v, w);
```

**Step 5: Quaternion Encoding** (`quat_from_mat3_cols`)

The $3 \times 3$ rotation matrix is converted to a unit quaternion $\mathbf{q} = (x, y, z, w)$ for compact GPU storage. Uses the standard matrix-to-quaternion algorithm (trace case vs. diagonal cases):

```c
t_vec4 quat_from_mat3_cols(t_mat3 m)
{
    trace = m.m[0][0] + m.m[1][1] + m.m[2][2];
    if (trace > 0.0f)
        return quat_from_trace(m, trace);   // largest component = w
    else
        return quat_from_diag(m, i);        // largest diagonal element
}
```

**Step 6: Projection and Extents** (`mat3_project_objects`)

All primitive vertices are projected onto the OBB basis axes, and the min/max extents along each axis define the OBB's half-extents:

$$
\text{half\_extents}_i = \frac{\text{max}_i - \text{min}_i}{2}
$$

## Splitting Algorithms

Three algorithms control how a parent node's primitives are partitioned into left and right children.

```c
typedef enum e_bvh_split
{
    MED_PRIM,      // median-split by primitive count
    MED_SPACE,     // median-split by spatial extent
    SAH            // surface area heuristic
} t_bvh_split;
```

### SAH — Surface Area Heuristic

The most sophisticated splitter. For each candidate split plane (evaluated via binning), the cost is:

$$
\text{Cost}(S) = C_t + \frac{A_L}{A_P} \cdot N_L \cdot C_i + \frac{A_R}{A_P} \cdot N_R \cdot C_i
$$

Where:
- $C_t$ = traversal cost (constant)
- $C_i$ = intersection cost (constant)
- $A_L, A_R$ = surface areas of left/right child bounds
- $A_P$ = surface area of parent bounds
- $N_L, N_R$ = primitive counts in left/right child

The split with the minimum cost is selected. If no split reduces cost, the node becomes a leaf.

**Binned SAH**: Instead of evaluating every primitive as a candidate split, the SAH uses fixed bins (typically 8–32) along the chosen axis, grouping primitives into bins to approximate the optimal split point efficiently.

### Median Primitive (MED_PRIM)

The primitives are sorted by centroid along the split axis, and the median index (half the primitives) is used as the split point. Both children get roughly equal primitive counts, producing a balanced tree but potentially poor spatial separation.

### Median Space (MED_SPACE)

The spatial extent along the split axis is divided in half. Primitives whose centroids fall on the left side go to the left child; those on the right go to the right child. This can produce unbalanced primitive counts but better spatial separation.

## Axis Selection

The split axis is selected by `get_axis_split()`, which evaluates the spread of primitive centroids along each axis:

- For **AABB**: The axis with the largest extent (max − min) is chosen.
- For **OBB**: The axis along which primitives have the largest projected spread, computed via `get_obb_projected_spread()`.
- For **Sphere**: The axis with the largest variance.

## GPU Data Structures

The CPU-side structures are transformed into compact GPU-friendly versions for OpenCL kernels.

### GPU Node

```c
typedef struct s_bvh_node_gpu
{
    union {
        int children[2];
        struct {
            int _pad[1];
            int object_id;
            int type;           // SPHERE or TRIANGLE
        };
    };
    int                skip;
    t_bvh_bounds_gpu   bounds;
} t_bvh_node_gpu;
```

### GPU Bounds Union

```c
typedef union u_bvh_bounds_gpu
{
    t_bvh_sphere_gpu  sphere;
    t_bvh_aabb_gpu    aabb;
    t_bvh_obb_gpu     obb;
} t_bvh_bounds_gpu;
```

### GPU Sphere

```c
typedef struct s_bvh_sphere_gpu
{
    union { float3 pos; float3 centroid; };
    union { float r; float radius; };
} t_bvh_sphere_gpu;
```

### GPU AABB

```c
typedef struct s_bvh_aabb_gpu
{
    union {
        struct { float3 min; float3 max; };
        t_cuboid cuboid;
    };
} t_bvh_aabb_gpu;
```

### GPU OBB

```c
typedef struct s_bvh_obb_gpu
{
    float3  center;
    float4  q;             // quaternion
    float3  half_extents;
    float4  axes[3];       // precomputed axes
} t_bvh_obb_gpu;
```

## GPU Traversal Functions

### `hit_aabb` — Slab Method

AABB intersection uses the **slab method**: the ray is tested against each pair of parallel planes, computing $t_{\text{min}}$ and $t_{\text{max}}$ per axis:

```c
bool hit_aabb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
    min_val = (bvh->bounds.aabb.min - ray->origin) * ray->inv_dir;
    max_val = (bvh->bounds.aabb.max - ray->origin) * ray->inv_dir;
    t_min = min(min_val.x, max_val.x);
    t_max = max(min_val.x, max_val.x);
    t_min = max(min(min_val.y, max_val.y), t_min);
    t_max = min(max(min_val.y, max_val.y), t_max);
    if (t_min > t_max) return false;
    t_min = max(min(min_val.z, max_val.z), t_min);
    t_max = min(max(min_val.z, max_val.z), t_max);
    if (t_min > t_max) return false;
    if (t_max < 0.0f) return false;
    return true;
}
```

### `hit_sphere` — Distance Test

Sphere intersection checks if the ray comes within the sphere's radius:

```c
int hit_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
    oc = ray->origin - bvh->bounds.sphere.pos;
    b = 2.0f * dot(ray->dir, oc);
    c = dot(oc, oc) - (bvh->bounds.sphere.radius * bvh->bounds.sphere.radius);
    discriminant = b * b - 4.0f * c;
    if (discriminant < 0) return 0;
    sqrt_d = sqrt(discriminant);
    t_min = (-b - sqrt_d) / 2.0f;
    t_max = (-b + sqrt_d) / 2.0f;
    if (t_min > 0) return 1;
    if (t_max > 0) return 1;
    return 0;
}
```

### `hit_obb` — Local Space Slab Test

OBB intersection transforms the ray into the OBB's local coordinate system using the **inverse quaternion rotation**, then performs a standard AABB slab test in that space:

```c
bool hit_obb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
    float4 qinv = (float4)(-bvh->bounds.obb.q.x, -bvh->bounds.obb.q.y,
                           -bvh->bounds.obb.q.z, bvh->bounds.obb.q.w);
    float3 local_origin = quat_rotate(qinv, ray->origin - bvh->bounds.obb.center);
    float3 local_dir    = quat_rotate(qinv, ray->dir);
    float3 inv_dir      = 1.0f / local_dir;
    float3 minb = -bvh->bounds.obb.half_extents;
    float3 maxb =  bvh->bounds.obb.half_extents;

    // Standard slab test against minb/maxb in local space
    // ...
}
```

The quaternion rotation function on GPU:

```c
inline float3 quat_rotate(float4 q, float3 v)
{
    float3 t = 2.0f * cross(q.xyz, v);
    return (v + q.w * t + cross(q.xyz, t));
}
```

### Full Traversal Loop

The top-level traversal (`hit_bvh_aabb`, `hit_bvh_sphere`, `hit_bvh_obb` in `shader/intersect.cl`) implements the roped-BVH pattern:

```c
int hit_bvh_aabb(ray, bvh, triangles, spheres, *t)
{
    nearest = -1;
    node = 0;
    while (node != -1)
    {
        if (hit_aabb(ray, &bvh[node]))
        {
            if (bvh[node].children[0] <= 0)   // leaf
            {
                if (intersect_triangle(ray, ...) || intersect_sphere(ray, ...))
                {
                    if (distance < *t) { *t = distance; nearest = node; }
                }
                node = bvh[node].skip;         // skip siblings
            }
            else
                ++node;                        // go to first child
        }
        else
            node = bvh[node].skip;             // skip this subtree
    }
    return nearest;
}
```

The dispatcher `hit_register_gpu()` selects which variant to use based on the `bvh_type` parameter:

```c
if (type == 0)      hit_bvh_sphere(ray, bvh, triangles, spheres, &t);
else if (type == 1) hit_bvh_aabb(ray, bvh, triangles, spheres, &t);
else                hit_bvh_obb(ray, bvh, triangles, spheres, &t);
```

## Indexing — Skip Pointer Computation

After construction, `index_bvh()` (in `src/calc/bvh/index_bvh.c`) computes the **skip pointers** that enable the flat-array iterative traversal:

```c
void index_recur(t_bvh_node *bvh, int idx)
{
    if (bvh[idx].children[0] <= 0) return;     // leaf, skip already set

    if (bvh[idx].children[1] > 0)
        bvh[idx + 1].skip = bvh[idx].children[1];   // left child's skip = right child
    else
        bvh[idx + 1].skip = bvh[idx].skip;          // inherit parent's skip

    index_recur(bvh, idx + 1);                       // recurse into left child

    if (bvh[idx].children[1] > 0)
    {
        bvh[bvh[idx].children[1]].skip = bvh[idx].skip;  // right child's skip = parent's skip
        index_recur(bvh, bvh[idx].children[1]);           // recurse into right child
    }
}
```

**Invariant**: The nodes array is stored in **depth-first order** with children[0] always at `node_idx + 1`. This means traversal never needs a stack — just `++node` to go to the first child, and `node = skip` to leave the subtree.

## BVH Debug System

The BVH debug system in `src/calc/bvh/bvh_debug/` provides detailed console output and visual overlays for understanding the tree structure.

### Debug Entry Points

| Function                   | Description                                    |
|----------------------------|------------------------------------------------|
| `debug_bvh_header()`       | Prints BVH metadata header                    |
| `debug_bvh_config()`       | Prints shape, splitting algo, build time      |
| `debug_bvh_stats()`        | Prints node count, leaf count, depth stats    |
| `debug_bvh_tree()`         | Prints full hierarchical tree                 |
| `debug_bvh_bounds()`       | Prints bounding volume details per node       |
| `debug_bvh_print()`        | Central dispatcher                            |

### Tree Printing

`print_bvh_node_tree()` renders the tree with Unicode box-drawing characters:

```
▎BVH Tree Structure

└── [0] <node> children=[1, 42] skip=-1 bounds=(AABB min=... max=...)
    ├── [1] <node> children=[2, 12] skip=42 bounds=(...)
    │   ├── [2] <node> children=[3, 7] skip=12 bounds=(...)
    │   │   ├── [3] leaf obj_id=5 skip=7 bounds=(...)
    │   │   └── [7] leaf obj_id=12 skip=12 bounds=(...)
    │   └── [12] leaf obj_id=3 skip=42 bounds=(...)
    └── [42] leaf obj_id=8 skip=-1 bounds=(...)
```

Each node shows:
- Array index in brackets
- Type (`leaf` or `<node>`)
- Children indices (for interior nodes) or object ID + type (for leaves)
- Skip pointer
- Bounding volume (formatted per shape type)

### Bounds Display

`print_bounds()` formats the bounds according to the active shape:

- **AABB**: `(AABB min=(x,y,z) max=(x,y,z))`
- **Sphere**: `(Sphere center=(x,y,z) r=radius)`
- **OBB**: `(OBB center=(x,y,z) q=(x,y,z,w) half=(x,y,z))`

### Color-Coded Console Output

The debug output uses ANSI escape sequences for readability:

| Element         | Color                    |
|-----------------|--------------------------|
| Header banner   | Purple bold italic       |
| Titles          | Light purple bold        |
| Leaf nodes      | Green bold               |
| Interior nodes  | Light blue bold          |
| Numbers         | Pink                     |
| Labels          | Teal italic              |
| Bounds values   | Light gray               |
| Tree lines      | Dark gray                |

### Statistics Display

`print_bvh_stats()` outputs:

```
  Node count:     127
  Leaf count:     64
  Max depth:      8
  Avg depth:      5.3
  Leaf ratio:     50.4%
  SAH cost:       12.7 (estimated)
```

### Visual Heat Map Overlay

When `data->params.bvh_debug` is enabled and the scene is rendered in wireframe mode, `debug_rasterize_bvh()` draws the BVH hierarchy on screen as colored outlines. Each node is color-coded by depth according to a rainbow gradient ($\text{hue} = \frac{\text{depth}}{\text{max\_depth}}$ mod 1.0).

## Pipeline Summary

```
Scene creation
    │
    ▼
clean_prim()        — extract spheres & triangles into a flat array
    │
    ▼
create_bvh()        — allocate nodes vector, call bvh_generator()
    │
    ▼
bvh_generator()
    ├─ evaluate_bounds()     — compute root bounding volume
    └─ bvh_subdivide()       — recursively split until leaf criteria met
         │
         ├─ evaluate_split() — choose splitter based on splitting_algo
         │    ├─ med_prim()   — median by count
         │    ├─ med_space()  — median by space
         │    └─ sah()        — surface area heuristic (binned)
         │
         └─ node.push_back() — append new node, recurse on children
    │
    ▼
index_bvh()         — compute skip pointers (depth-first order)
    │
    ▼
debug_bvh_tree()    — print tree structure
    │
    ▼
set_type()          — set object type (SPHERE/TRIANGLE) on leaf nodes
    │
    ▼
GPU upload          — bvh_gpu = clCreateBuffer(bvh_header->nodes)
    │
    ▼
Ray tracing kernel  — hit_register_gpu() traverses via skip pointers
```