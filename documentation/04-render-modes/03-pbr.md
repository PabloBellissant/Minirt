# Render Mode: PBR (Mode 2)

PBR (Physically Based Rendering) mode extends the basic Phong model with
**Fresnel reflectance, reflections, refractions, and multi-bounce light
transport**. It uses the Schlick approximation for Fresnel and supports both
dielectric and metallic materials.

---

## 1. Fresnel Reflectance

### 1.1. F0 — Fresnel Reflectance at Normal Incidence

The Fresnel reflectance at normal incidence ($F_0$) is computed from the
material's index of refraction ($\eta$):

$$F_0 = \left(\frac{\eta - 1}{\eta + 1}\right)^2$$

For common materials:

| Material | $\eta$ | $F_0$ |
|---|---|---|
| Air | 1.00 | 0.0 |
| Water | 1.33 | 0.02 |
| Glass | 1.50 | 0.04 |
| Diamond | 2.42 | 0.17 |

For **metals**, $F_0$ is blended with the specular color ($k_s$) based on
metalness ($Pm$):

$$F_0 = \text{mix}(F_0_{\text{dielectric}}, k_s, Pm)$$

This allows the same Fresnel equations to handle both dielectric and metallic
surfaces.

### 1.2. Schlick Fresnel Approximation

The Fresnel reflectance at angle $\theta$ is approximated by the **Schlick
approximation**:

$$F(\theta) = F_0 + (1 - F_0)(1 - \cos\theta)^5$$

where $\cos\theta = |\vec{D} \cdot \vec{N}|$ is the absolute cosine of the
angle between the ray direction and the surface normal.

This equation gives:

- At normal incidence ($\theta = 0^\circ$, $\cos\theta = 1$): $F = F_0$
- At grazing incidence ($\theta = 90^\circ$, $\cos\theta = 0$): $F = 1.0$

Grazing angles always reflect — every surface becomes a mirror at glancing
angles.

### 1.3. Glossy Factor

Surface roughness reduces reflectivity. The **glossy factor** is computed from
the material roughness ($Pr$):

$$\alpha = Pr^2$$

$$\text{glossy} = 1 - \alpha$$

where $\alpha$ is the roughness squared (the GGX alpha parameter).

The final reflectivity is:

$$\text{reflectivity} = F(\theta) \cdot \text{glossy}$$

clamped to $[0, 1]$.

Smooth surfaces ($\alpha \approx 0$) have $\text{glossy} \approx 1$ and follow
the Fresnel curve exactly. Rough surfaces ($\alpha \approx 1$) have
$\text{glossy} \approx 0$ and reflect very little.

---

## 2. Reflection vs. Refraction

At each bounce, the kernel decides whether to **reflect** or **refract** based
on the material's opacity ($d$):

```
if random_float() > material.opacity:
    refract (transmit through the surface)
else:
    reflect
```

### 2.1. Reflection

When reflecting, the ray direction is computed by the standard reflection
formula:

$$\vec{R} = \vec{D} - 2(\vec{D} \cdot \vec{N})\vec{N}$$

### 2.2. Refraction (Snell's Law)

When refracting, the direction follows Snell's law:

$$\eta = \frac{n_1}{n_2}$$

where $n_1$ is the IOR of the incident medium (usually 1.0 for air) and $n_2$
is the material's IOR ($Ni$).

The refracted direction is:

$$\cos\theta_i = -\text{dot}(\vec{D}, \vec{N})$$

$$\cos^2\theta_t = 1 - \eta^2 \cdot (1 - \cos^2\theta_i)$$

If $\cos^2\theta_t < 0$, **total internal reflection** occurs — the ray
reflects instead.

Otherwise:

$$\cos\theta_t = \sqrt{\cos^2\theta_t}$$

$$\vec{T} = \vec{D} \cdot \eta + \vec{N} \cdot (\eta \cdot \cos\theta_i - \cos\theta_t)$$

---

## 3. Bounce Loop

The PBR kernel executes up to `MAX_BOUNCE = 4` bounces per pixel.

### 3.1. Per-Bounce Flow

```
For bounce = 0 to MAX_BOUNCE - 1:

    1. Cast ray from current origin, trace BVH
    2. If no hit:
         accumulated += skybox_color * through_power
         break
    3. Sample materials (normal map, roughness, metalness from textures)
    4. Compute F0 from Ni, blend with ks if metal
    5. Compute Schlick Fresnel F(θ) from F0 and cosθ
    6. Compute glossy = 1 - α (where α = roughness²)
    7. Compute reflectivity = clamp(F * glossy, 0, 1)

    8. Add direct contribution to accumulated color:
       accumulated += phong_shading(...) * (1 - reflectivity) * through_power

    9. Update through_power:
       through_power *= reflectivity

    10. Decide: reflect or refract based on opacity
        - If refract: compute ray via Snell's law
        - If reflect: compute ray via reflection formula
        
    11. Next bounce continues with new ray
```

### 3.2. Through-Power Attenuation

The `through_power` variable tracks how much light energy remains in the path
after successive reflections/refractions. It starts at $(1, 1, 1)$ and is
multiplied by `reflectivity` at each bounce.

At each bounce, the surface's direct contribution (Phong shading) is added to
the accumulated color, weighted by `(1 - reflectivity) * through_power`. The
remaining energy (`through_power *= reflectivity`) continues to the next bounce.

This ensures **energy conservation**: the sum of reflected + transmitted energy
equals the incident energy (ignoring absorption).

### 3.3. Skybox Termination

When a ray misses all geometry, the skybox color is sampled and added to the
accumulation, weighted by the current `through_power`. The bounce loop then
terminates.

---

## 4. Complete Kernel Flow

```
pbr_kernel(pixel_x, pixel_y):
    1. Generate camera ray (with optional DOF jitter)
    2. Initialize through_power = (1, 1, 1)
    3. Initialize accumulated_color = (0, 0, 0)

    4. For bounce = 0 to MAX_BOUNCE-1:
        a. Trace ray → nearest hit
        b. If no hit → accumulated += skybox * through_power; break
        c. Sample materials (textures → kd, normal, roughness, etc.)
        d. Compute F0, Fresnel, glossy, reflectivity
        e. accumulated += phong_shading (...) * (1 - reflectivity) * through_power
        f. through_power *= reflectivity
        g. If through_power is negligible → break (optimization, but not implemented)
        h. Compute new ray direction (reflect or refract)
        i. Update ray origin = hit_point (with small epsilon offset)

    5. accu[pixel] += accumulated_color
```

---

## 5. Material Parameters Used

| MTL Parameter | PBR Role |
|---|---|
| `Kd` | Diffuse albedo |
| `Ks` | Specular color (tints reflection for metals) |
| `Ke` | Emissive color |
| `Ni` | Index of refraction (Fresnel + refraction) |
| `d` | Opacity (reflection vs. refraction decision) |
| `Pr` | Roughness (squared = GGX alpha) |
| `Pm` | Metalness (blends F0) |
| `Ns` | Shininess (Phong specular component only) |
| `map_Kd`, `map_bump`, `map_Pr`, `map_Ka`, `map_d`, `map_Pm` | Texture maps |

---

## 6. Performance

PBR mode is slower than Phong because each pixel may require up to `MAX_BOUNCE`
ray casts (4× the intersection work). However, it is significantly faster than
Monte Carlo mode because:

- No importance sampling of the BRDF (uses deterministic reflection/refraction)
- No multiple samples per pixel (path tracing accumulates over frames)
- Direct Phong contribution at each bounce is cheap

Typical performance: 5–30 frames per second on modern GPUs depending on scene
complexity.