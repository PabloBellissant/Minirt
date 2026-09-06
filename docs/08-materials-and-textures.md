# Materials and Textures

## Overview

miniRT supports a full PBR material system with 6 texture map types, a
flat texture atlas for GPU access, per-pixel normal mapping with TBN
transforms, and both 3-channel (RGB) and 1-channel (grayscale) texture
sampling on the GPU.

---

## The `t_mat` Struct

Materials are defined in `include/object.h` (lines 37-52) and mirrored on the
GPU as `t_mat_gpu` in `shader/include/gpu.cl` (lines 77-92):

```c
typedef struct s_mat
{
    char            *name;      // Material name (matches MTL or .rt reference)
    cl_float        ns;         // Shininess / specular exponent (Phong)
    cl_float3       kd;         // Diffuse color (albedo)
    cl_float3       ks;         // Specular color (reflectance at normal incidence, F0)
    cl_float3       ke;         // Emissive color
    cl_float        opacity;    // Opacity (d): 1.0 = opaque, 0.0 = fully transparent
    t_texture_data  kd_id;      // Diffuse / albedo texture map
    t_texture_data  normal_id;  // Normal map
    t_texture_data  roughness_id; // Roughness map
    t_texture_data  ambient_id;   // Ambient occlusion / ambient map
    t_texture_data  opacity_id;   // Opacity texture map
    t_texture_data  metalness_id; // Metalness map
    cl_float        ni;         // Index of refraction
}               t_mat;
```

### PBR Properties

| Field | MTL Equivalent | Description |
|-------|----------------|-------------|
| `Ns` | `Ns` | Specular exponent (shininess). Range [0, ∞). Higher = sharper highlights. |
| `Kd` | `Kd` | Diffuse albedo (base color). Used as the diffuse reflectance. |
| `Ks` | `Ks` | Specular color / F0. For metals, this is the reflectance color. |
| `Ke` | `Ke` | Emissive color. Non-zero → surface acts as a light source. |
| `Pr` | (via roughness map) | **Roughness** — sampled from `roughness_id` texture. Controls microfacet distribution spread. |
| `Pm` | (via metalness map) | **Metalness** — sampled from `metalness_id` texture. Blends between dielectric and metallic F0. |
| `Ni` | `Ni` | Index of refraction. Used for Fresnel (dielectric F0) and Snell's law refraction. |
| `d` | `d` | Opacity (dissolve). 1.0 = fully opaque, 0.0 = fully transparent. |
| `Ka` | `Ka` | Ambient color — sampled from `ambient_id` as grayscale AO factor. |

### GPU-Side Material Sampling

The GPU kernel `sample_materials()` in `shader/sample_materials.cl` assembles
a `t_hit_data` struct from the material + textures at the hit point:

```c
t_hit_data sample_materials(__private t_hit_gpu *hit,
    __constant uchar *tex, __constant t_mat_gpu *mat,
    __private t_ray_gpu *ray)
{
    hit_data.kd  = sample_texture(tex, hit->uv, &mat[hit->mat_id].kd_id);
    hit_data.ambient = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].ambient_id);
    hit_data.ks  = mat[hit->mat_id].ks;
    hit_data.ke  = mat[hit->mat_id].ke;
    hit_data.ns  = mat[hit->mat_id].ns;
    // Normal map perturbation
    nmap = sample_texture(tex, hit->uv, &mat[hit->mat_id].normal_id);
    tangent = get_tangent(hit->normal);
    bitangent = cross(hit->normal, tangent);
    hit_data.normal = apply_normal_map(hit->normal, nmap, tangent, bitangent);
    // PBR texture maps
    hit_data.metalness = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].metalness_id);
    hit_data.roughness = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].roughness_id);
    hit_data.opacity   = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].opacity_id);
    // Fresnel
    f0 = get_f0(hit_data.metalness, mat[hit->mat_id].ni, hit_data.ks);
    hit_data.reflectivity = get_reflect(ray->dir, hit_data.normal, hit_data.roughness, f0);
    hit_data.ni = mat[hit->mat_id].ni;
}
```

---

## Texture Map Types

miniRT supports **6 texture map types** per material. Each map is an
optional `t_texture_data` descriptor pointing into the global texture atlas.

| Map | Channels | Sampling Function | Usage |
|-----|----------|-------------------|-------|
| `kd_id` | 3 (RGB) | `sample_texture()` | Diffuse/albedo color |
| `normal_id` | 3 (RGB) | `sample_texture()` + TBN | Normal perturbation |
| `roughness_id` | 1 (grayscale) | `sample_gray_level_texture()` | Roughness [0,1] |
| `ambient_id` | 1 (grayscale) | `sample_gray_level_texture()` | Ambient occlusion [0,1] |
| `opacity_id` | 1 (grayscale) | `sample_gray_level_texture()` | Opacity mask [0,1] |
| `metalness_id` | 1 (grayscale) | `sample_gray_level_texture()` | Metalness [0,1] |

---

## Texture Atlas

All loaded textures are concatenated into a single flat byte array
(`__constant uchar *textures` on the GPU) called the **texture atlas**. Each
texture is described by a `t_texture_data` struct:

```c
typedef struct s_texture_data
{
    int index;      // Texture index in the scene's texture vector
    int offset;     // Byte offset into the atlas
    int width;      // Texture width in pixels
    int height;     // Texture height in pixels
    int channels;   // Number of channels (3 for RGB, 1 for grayscale)
}   t_texture_data;
```

### Per-Pixel Sampling (GPU)

**RGB texture sampling** (`sample_texture.cl`):

```c
rgb3 sample_texture(__constant uchar *textures, float2 uv,
                    __constant t_texture_data *data)
{
    int x = (int)(uv.x * (float)(data->width));
    int y = (int)(uv.y * (float)(data->height));
    int offset = data->offset;
    offset += y * (data->width * data->channels) + x * data->channels;
    color.x = textures[offset];       // R
    color.y = textures[offset + 1];   // G
    color.z = textures[offset + 2];   // B
    return (rgb3)(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f);
}
```

**Grayscale texture sampling** (single-channel maps):

```c
float sample_gray_level_texture(__constant uchar *textures, float2 uv,
                                __constant t_texture_data *data)
{
    int x = (int)(uv.x * (float)(data->width));
    int y = (int)(uv.y * (float)(data->height));
    int offset = data->offset;
    offset += y * data->width + x;   // 1 channel — no channels multiplier
    pixel = textures[offset];
    return ((float)pixel / 255.0f);
}
```

---

## Normal Map TBN Transform

Normal maps store normals in tangent space. The GPU applies a
tangent-bitangent-normal (TBN) transform to convert them to world space.

### Tangent Calculation

```c
static float3 get_tangent(float3 n)
{
    float3 up;
    if (fabs(n.y) > 0.999f)
        up = (float3)(1, 0, 0);
    else
        up = (float3)(0, 1, 0);
    return (normalize(cross(up, n)));
}
```

### World-Space Transform

```c
static float3 apply_normal_map(float3 normal, float3 nmap,
                               float3 tangent, float3 bitangent)
{
    float3 n = nmap * 2.0f - 1.0f;  // Uncompress from [0,1] to [-1,1]
    float3 world_normal = (tangent * n.x) + (bitangent * -n.y) + (normal * n.z);
    return (normalize(world_normal));
}
```

### Bitangent

The bitangent is computed as `cross(normal, tangent)` and the Y component
of the normal map is negated (`-n.y`) to account for the OpenGL convention
(where V texture coordinate increases downward, opposite of the math
convention).

---

## Material Diagrams

```mermaid
flowchart TD
    subgraph Scene
        MAT["t_mat[]<br/>Material Array"]
        TEX_ATLAS["__constant uchar[]<br/>Texture Atlas"]
    end
    
    subgraph Material
        M_NAME["name"]
        M_NS["Ns (shininess)"]
        M_KD["Kd (diffuse)"]
        M_KS["Ks (specular/F0)"]
        M_KE["Ke (emissive)"]
        M_OP["d (opacity)"]
        M_NI["Ni (IOR)"]
        M_KD_ID["kd_id (t_texture_data)"]
        M_NORM_ID["normal_id"]
        M_ROUGH_ID["roughness_id"]
        M_AMB_ID["ambient_id"]
        M_OP_ID["opacity_id"]
        M_MET_ID["metalness_id"]
    end
    
    subgraph TextureAtlas
        TEX_KD["Diffuse Map<br/>3-channel RGB<br/>→ sample_texture()"]
        TEX_NORM["Normal Map<br/>3-channel RGB<br/>→ TBN transform"]
        TEX_ROUGH["Roughness Map<br/>1-channel gray<br/>→ sample_gray()"]
        TEX_AMB["AO Map<br/>1-channel gray<br/>→ sample_gray()"]
        TEX_OP["Opacity Map<br/>1-channel gray<br/>→ sample_gray()"]
        TEX_MET["Metalness Map<br/>1-channel gray<br/>→ sample_gray()"]
    end
    
    M_KD_ID --> TEX_KD
    M_NORM_ID --> TEX_NORM
    M_ROUGH_ID --> TEX_ROUGH
    M_AMB_ID --> TEX_AMB
    M_OP_ID --> TEX_OP
    M_MET_ID --> TEX_MET
    
    subgraph "GPU Hit Data (t_hit_data)"
        HD_KD["kd (float3) ← diffuse texture"]
        HD_AMB["ambient (float) ← AO texture"]
        HD_KS["ks (float3) ← mat.ks"]
        HD_KE["ke (float3) ← mat.ke"]
        HD_NS["ns (float) ← mat.ns"]
        HD_NORMAL["normal (float3) ← normal map\nperturbed via TBN"]
        HD_METAL["metalness (float) ← metalness tex"]
        HD_ROUGH["roughness (float) ← roughness tex"]
        HD_OPACITY["opacity (float) ← opacity tex"]
        HD_REFLECT["reflectivity (float3)\nSchlick Fresnel"]
        HD_NI["ni (float) ← mat.ni"]
    end
    
    MAT --> M_KD_ID
    TEX_ATLAS --> TEX_KD
    TEX_KD --> HD_KD
    TEX_NORM --> HD_NORMAL
    TEX_ROUGH --> HD_ROUGH
    TEX_AMB --> HD_AMB
    TEX_OP --> HD_OPACITY
    TEX_MET --> HD_METAL
    M_KS --> HD_KS
    M_KE --> HD_KE
    M_NS --> HD_NS
    M_NI --> HD_NI
    HD_METAL --> HD_REFLECT
    HD_ROUGH --> HD_REFLECT
    HD_KS --> HD_REFLECT
    M_NI --> HD_REFLECT
```

---

## Fresnel (F0) Calculation

The `get_f0()` function computes the Fresnel reflectance at normal incidence
(F0), blending between dielectric and metallic behavior:

```c
rgb3 get_f0(float metalness, float ior, rgb3 ks)
{
    float no_metal = ((ior - 1.0f) / (ior + 1.0f));
    no_metal *= no_metal;               // Dielectric F0 (Schlick approximation)
    return (mix((float3)no_metal, ks, metalness)); // Blend with metallic F0
}
```

- **Dielectric** (metalness = 0): F0 is a scalar computed from IOR.
  For glass (IOR ≈ 1.5), F0 ≈ 0.04.
- **Metal** (metalness = 1): F0 is the specular color (`ks`), which is the
  actual reflectance color of the metal (e.g., gold → yellowish).
- **Mixed**: Linear interpolation between the two.

---

## Reflectivity (Glossy Factor)

```c
float3 get_reflect(float3 ray_dir, float3 normal, float roughness, float3 F0)
{
    cos_theta = fabs(dot(ray_dir, normal));
    fresnel = (1 - F0) * (pow(1.0f - cos_theta, 5.0f)) + F0;  // Schlick
    glossy_factor = 1.0f - (roughness * roughness);            // Roughness → gloss
    return (clamp(fresnel * glossy_factor, 0.0f, 1.0f));
}
```

The Schlick approximation computes Fresnel reflectance as a function of
viewing angle. The result is modulated by roughness (smoother surfaces =
more reflective) and clamped to [0, 1].

---

## Refraction (Snell's Law)

The `refract()` function in `sample_materials.cl` handles refraction:

```c
float3 vec3_refract(float3 ray_dir, float3 normal, float eta)
{
    cosi = -dot(ray_dir, normal);
    cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
    if (cost2 < 0.0001f) return (0);  // Total internal reflection
    cost = sqrt(cost2);
    return (normalize(ray_dir * eta + normal * (eta * cosi - cost)));
}
```

The function handles entering (IOR ratio = 1/ni) and exiting (IOR ratio = ni)
a refractive material. Total internal reflection is detected when `cost2 < 0`.

In Monte Carlo mode, chromatic dispersion is added via `get_ni_by_color()`,
which perturbs the IOR based on the hue of the accumulated light, producing
rainbow-like caustics.