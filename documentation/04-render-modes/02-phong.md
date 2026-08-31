# Render Mode: Phong (Mode 1)

Phong mode implements the **Phong reflection model** — the classic shading
approach that decomposes surface illumination into ambient, diffuse, and
specular components. This is the shading model required by the original 42
School miniRT subject.

---

## 1. Shading Model

The Phong model computes the color at a surface point as:

$$I_{\text{total}} = I_{\text{ambient}} + \sum_{j} \left( I_{\text{diffuse},j} + I_{\text{specular},j} \right) + I_{\text{emissive}}$$

### 1.1. Ambient Component

The ambient term provides a constant base illumination, simulating indirect
lighting:

$$I_{\text{ambient}} = \text{ambient}_{\text{color}} \times k_a$$

where $\text{ambient}_{\text{color}}$ comes from the scene's `A` directive and
$k_a$ is the material's ambient color (`Ka` in MTL).

### 1.2. Diffuse Component (Lambertian)

The diffuse term models light scattering equally in all directions. It follows
**Lambert's cosine law**:

$$I_d = k_d \cdot I_l \cdot \max(0, \vec{L} \cdot \vec{N})$$

where:

- $k_d$ = material diffuse color (`Kd`)
- $I_l$ = light color and intensity
- $\vec{L}$ = normalized light-to-surface direction
- $\vec{N}$ = surface normal at the hit point

The $\max(0, \cdot)$ clamp ensures that surfaces facing away from the light
receive no diffuse contribution.

### 1.3. Specular Component (Phong)

The specular term models bright highlights on shiny surfaces. It depends on the
view direction:

$$I_s = k_s \cdot I_l \cdot \max(0, \vec{R} \cdot \vec{V})^{n_s}$$

where:

- $k_s$ = material specular color (`Ks`)
- $\vec{R}$ = reflected light direction: $\vec{R} = 2(\vec{L} \cdot \vec{N})\vec{N} - \vec{L}$
- $\vec{V}$ = normalized surface-to-camera direction
- $n_s$ = shininess exponent (`Ns`) — higher values give sharper, smaller highlights

The reflect function computes:

$$\vec{R} = \text{reflect}(\vec{L}, \vec{N}) = 2 \cdot \text{dot}(\vec{L}, \vec{N}) \cdot \vec{N} - \vec{L}$$

### 1.4. Emissive Component

Materials with an emissive color ($k_e$ / `Ke`) add their own light:

$$I_{\text{emissive}} = k_e$$

This makes the surface appear to glow. Emissive materials do not illuminate
other surfaces in Phong mode (that requires path tracing).

### 1.5. Shadow Rays

For each light, a **shadow ray** is cast from the hit point toward the light:
if any geometry occludes the path, the diffuse and specular contributions from
that light are suppressed (only ambient remains).

The shadow test:

```
1. Cast ray: origin = hit_point, direction = normalize(light_pos - hit_point)
2. distance² = dot(light_pos - hit_point, light_pos - hit_point)
3. If any intersection has t > 0 and t² < distance² → light is blocked
4. If blocked → skip diffuse + specular for this light
```

### 1.6. Final Color

Each color channel is clamped to [0, 1]:

$$C_{\text{final}} = \text{clamp}(I_{\text{total}}, 0, 1)$$

---

## 2. Per-Pixel Kernel Flow

The Phong kernel (`phong.cl`) executes one work-item per pixel and follows
this flow:

```
phong_kernel(pixel_x, pixel_y):
    1. Generate ray
       - Compute pixel center in world space from camera basis
       - ray.origin = camera.pos
       - ray.direction = normalize(pixel_center - camera.pos)

    2. Trace ray through scene
       - Traverse BVH (BVH2/4/8)
       - For each candidate primitive: test intersection
       - Keep nearest hit (minimum t)

    3. If no hit → sample skybox (if available) or return background color

    4. If hit → compute Phong shading:
       a. Get material properties (kd, ks, ke, ns) from hit object
       b. Apply normal map (if present) via tangent-space TBN transform
       c. Initialize color = ambient_light * ka
       d. For each light:
           - Compute L = normalize(light_pos - hit_point)
           - Cast shadow ray
           - If not shadowed:
               diffuse  = kd * light_color * max(0, dot(L, N))
               R        = reflect(L, N)
               V        = normalize(camera_pos - hit_point)
               specular = ks * light_color * max(0, dot(R, V))^ns
               color   += diffuse + specular
       e. color += ke (emissive)
       f. color  = clamp(color, 0, 1)

    5. accu[pixel] += color
```

---

## 3. Material Parameters

| MTL Parameter | Phong Role |
|---|---|
| `Kd` | Diffuse color $k_d$ |
| `Ks` | Specular color $k_s$ |
| `Ke` | Emissive color $k_e$ |
| `Ns` | Shininess exponent $n_s$ (higher = sharper highlights) |
| `Ka` | Ambient color multiplier $k_a$ |
| `map_Kd` | Diffuse texture (sampled, multiplied with `Kd`) |
| `map_bump` | Normal map (perturbs $\vec{N}$) |

Opacity (`d`), roughness (`Pr`), metalness (`Pm`), and index of refraction
(`Ni`) are not used in Phong mode — they are PBR-specific properties.

---

## 4. Performance

Phong mode is the **fastest** GPU rendering mode. Each pixel requires:

- 1 primary ray (BVH traversal + primitive intersection)
- $N$ shadow rays (one per light)
- No secondary bounces, no recursion

Typical performance: tens to hundreds of frames per second depending on scene
complexity and GPU.

---

## 5. Limitations

- No reflections or refractions (one-bounce-only)
- No soft shadows (hard shadows from point lights)
- No physically based attenuation or energy conservation
- Emissive surfaces don't illuminate other surfaces
- Highlights use ad-hoc Phong exponent rather than microfacet BRDF