# BVH System

![BVH tree structure diagram](docs/assets/svg/bvh-tree.svg)
*Visualization of the BVH tree structure showing the root node splitting into child subtrees with different bounding volume shapes (AABB, Sphere, OBB) and leaf nodes containing primitives.*

The **Bounding Volume Hierarchy (BVH)** accelerates ray-scene intersection by organizing primitives in a spatial tree. Each node stores a bounding volume that encloses all primitives in its subtree. During traversal, nodes whose bounding volume is missed by the ray are skipped, yielding $O(\log n)$ average intersection time.

## Architecture Overview

*Diagram showing the CPU-side build pipeline and GPU-side traversal loop.*

```mermaid
flowchart TD
    subgraph CPU ["CPU - Scene Setup"]
        SCE[Scene Objects] --> CLEAN[clean_prim\n filter spheres & triangles]
        CLEAN --> CREATE[create_bvh\n select shape + splitting]
        CREATE --> INDEX[index_bvh\n compute skip pointers]
        INDEX --> DEBUG[debug_bvh_tree\n print tree + stats]
        INDEX --> GPU_UPLOAD[Upload to GPU\n clCreateBuffer]
    end

    subgraph GPU ["GPU - Ray Tracing"]
        RAY[Primary Ray] --> TRAVERSE[BVH Traversal\n hit_bvh_{sphere,aabb,obb}]
        TRAVERSE --> HIT{Node hit?}
        HIT -->|Yes| IS_LEAF{Is leaf?}
        IS_LEAF -->|Yes| INTERSECT[Intersect primitive\n triangle / sphere]
        IS_LEAF -->|No| GO_CHILD[++node -> first child]
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

`world_bvh` holds the active world BVH header. `world_best_bvh` is a reference to a "best" BVH used for comparison and testing. `bvh_gpu` is the OpenCL memory buffer holding the GPU-compact array of `t_bvh_node_gpu`.

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

**Interior nodes** use `children[0]` and `children[1]` as positive indices into the nodes array. **Leaf nodes** have `children[0] <= 0`, with `object_id` indexing the primitive and `type` identifying the primitive type. The **skip pointer** enables the "roped BVH" pattern - after processing a node, traversal jumps to `skip` instead of returning to parent, allowing a flat-array iterative approach without recursion.

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

*Visual comparison of axis-aligned (AABB), sphere, and oriented (OBB) bounding volumes around the same geometry.*

### 1. AABB - Axis-Aligned Bounding Box

```c
typedef struct s_bvh_aabb
{
    union {
        struct { t_vec3 min; t_vec3 max; };
        t_cuboid cuboid;
    };
} t_bvh_aabb;
```

The AABB is defined by `min` and `max` corners, evaluated by finding the extent of all primitive centroids and vertices in each axis. It offers the fastest GPU intersection test using the slab method (no rotation transform needed), making it ideal for axis-aligned scenes but wasteful for rotated geometry.

### 2. Sphere Bounding Volume

```c
typedef struct s_bvh_sphere
{
    union { t_vec3 pos; t_vec3 centroid; };
    union { float r; float radius; };
} t_bvh_sphere;
```

The sphere bound is defined by a center position and a radius, evaluated by computing the centroid of all primitives then finding the maximum distance. It has the simplest intersection test (point-in-sphere distance) but tends to produce more overlap between sibling nodes, reducing BVH efficiency.

### 3. OBB - Oriented Bounding Box

*Pipeline diagram showing the steps from PCA mean computation through to the final oriented bounding box.*

```c
typedef struct s_bvh_obb
{
    t_vec3  center;
    t_vec4  q;              // rotation quaternion
    t_vec3  half_extents;   // half-size along each axis
    t_vec3  axes[3];        // pre-computed basis axes from quaternion
} t_bvh_obb;
```

The OBB is the tightest-fitting box for arbitrarily oriented geometry. It uses **PCA (Principal Component Analysis)** to find the dominant orientation of the primitive vertices.

#### OBB Construction Pipeline

```mermaid
flowchart LR
    subgraph PCA ["PCA Computation"]
        MEAN[get_pca_mean\n centroid of all vertices] --> COV[get_pca_covariance\n 3x3 covariance matrix]
        COV --> JACOBI[mat3_eigh_jacobi\n Jacobi eigenvalue decomposition]
    end

    subgraph Basis ["Basis Extraction"]
        JACOBI --> SORT[sort3_desc\n sort eigenvalues descending]
        SORT --> BASIS[basis3_from_eigh\n orthogonalize basis via cross product]
    end

    subgraph Quaternion ["Quaternion Encoding"]
        BASIS --> QUAT[quat_from_mat3_cols\n convert rotation matrix -> quaternion]
        QUAT --> AXES[obb_axes_from_quat\n compute axes[0..2] from quaternion]
    end

    subgraph Extents ["Extent Computation"]
        AXES --> PROJECT[mat3_project_objects\n project vertices onto basis]
        PROJECT --> EXTENTS[min/max -> half_extents]
    end
```

**Step 1: PCA Mean** (`get_pca_mean`) computes the mean position of all primitive vertices, where for triangles each of the three vertices contributes $\frac{1}{3N}$ to the sum.

**Step 2: PCA Covariance** (`get_pca_covariance`) computes the $3 \times 3$ covariance matrix from the centered data, resulting in a symmetric matrix.

**Step 3: Jacobi Eigenvalue Decomposition** (`mat3_eigh_jacobi`) diagonalizes the covariance matrix via successive Givens rotations (up to 45 iterations with tolerance $1.0 \times 10^{-9}$). The diagonalized matrix's diagonal entries are the eigenvalues, and the accumulated rotation matrix is the eigenvector matrix.

**Step 4: Basis Sorting** (`basis3_from_eigh`) sorts eigenvalues descending and takes corresponding eigenvectors as the new basis axes. A Gram-Schmidt-like orthogonalization via cross products ensures a right-handed orthonormal basis.

**Step 5: Quaternion Encoding** (`quat_from_mat3_cols`) converts the $3 \times 3$ rotation matrix to a unit quaternion for compact GPU storage, using the standard matrix-to-quaternion algorithm with trace case vs. diagonal case branching.

**Step 6: Projection and Extents** (`mat3_project_objects`) projects all primitive vertices onto the OBB basis axes, computing half-extents from the min/max along each axis.

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

### SAH - Surface Area Heuristic

The most sophisticated splitter evaluates candidate split planes via binning. For each candidate, the cost is:

$$\text{Cost}(S) = C_t + \frac{A_L}{A_P} \cdot N_L \cdot C_i + \frac{A_R}{A_P} \cdot N_R \cdot C_i$$

Where $C_t$ is traversal cost, $C_i$ is intersection cost, $A_L$ and $A_R$ are surface areas of left and right child bounds, $A_P$ is the surface area of the parent bound, and $N_L$ and $N_R$ are primitive counts in each child. The split with minimum cost is selected; if no split reduces cost, the node becomes a leaf. The binned SAH approach uses fixed bins (typically 8-32) along the chosen axis to approximate the optimal split point efficiently.

### Median Primitive (MED_PRIM)

Primitives are sorted by centroid along the split axis and the median index is used as the split point. Both children get roughly equal primitive counts, producing a balanced tree but potentially poor spatial separation.

### Median Space (MED_SPACE)

The spatial extent along the split axis is divided in half. Primitives whose centroids fall on the left side go to the left child; those on the right go to the right child. This can produce unbalanced primitive counts but better spatial separation.

## Axis Selection

The split axis is selected by `get_axis_split()`, which evaluates the spread of primitive centroids along each axis. For AABB, the axis with the largest extent (max minus min) is chosen. For OBB, the axis along which primitives have the largest projected spread is used, computed via `get_obb_projected_spread()`. For Sphere, the axis with the largest variance is selected.

## GPU Data Structures

The CPU-side structures are transformed into compact GPU-friendly versions for OpenCL kernels. The GPU node struct mirrors its CPU counterpart but uses OpenCL `float3`/`float4` types and is stored in `__constant` memory for fast access. The bounds union on the GPU similarly mirrors the CPU version with `t_bvh_sphere_gpu`, `t_bvh_aabb_gpu`, and `t_bvh_obb_gpu` variants, each using OpenCL vector types for better memory alignment.

## GPU Traversal Functions

*Animated visualization of the ray traversal through a BVH tree, showing which nodes are visited and skipped.*

### `hit_aabb` - Slab Method

AABB intersection uses the **slab method**: the ray is tested against each pair of parallel planes, computing $t_{\min}$ and $t_{\max}$ per axis using the precomputed inverse ray direction.

### `hit_sphere` - Distance Test

Sphere intersection checks if the ray comes within the sphere's radius using the standard ray-sphere quadratic equation: $b = 2(\hat{D} \cdot \text{oc})$, $c = \text{oc} \cdot \text{oc} - r^2$, with the discriminant determining whether an intersection exists.

### `hit_obb` - Local Space Slab Test

OBB intersection transforms the ray into the OBB's local coordinate system using the **inverse quaternion rotation**, then performs a standard AABB slab test in that local space. The quaternion rotation on the GPU is computed via `quat_rotate()`: $\mathbf{v}' = \mathbf{v} + q_w \cdot 2(\mathbf{q}_{xyz} \times \mathbf{v}) + 2(\mathbf{q}_{xyz} \times (\mathbf{q}_{xyz} \times \mathbf{v}))$.

### Full Traversal Loop

The top-level traversal functions (`hit_bvh_aabb`, `hit_bvh_sphere`, `hit_bvh_obb` in `shader/intersect.cl`) implement the roped-BVH pattern using an iterative while loop over the flat node array. The loop starts at node 0 and uses the skip pointer to advance past finished subtrees. A dispatcher `hit_register_gpu()` selects the appropriate variant based on the `bvh_type` parameter (0 = sphere, 1 = AABB, 2 = OBB).

## Indexing - Skip Pointer Computation

After construction, `index_bvh()` (in `src/calc/bvh/index_bvh.c`) computes the **skip pointers** that enable the flat-array iterative traversal. For each node, the skip pointer is set to the next sibling of the nearest ancestor, or -1 if no such sibling exists. This transforms the recursive tree into a flat array where traversal can proceed linearly without a stack.