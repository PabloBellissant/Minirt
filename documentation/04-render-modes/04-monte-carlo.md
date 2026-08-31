# Render Mode: Monte Carlo (Mode 3)

Monte Carlo mode implements **path tracing** with importance-sampled GGX
microfacet scattering, chromatic dispersion, and progressive accumulation.
This is the most physically accurate render mode in miniRT.

---

## 1. GGX/Trowbridge-Reitz Microfacet Sampling

At each bounce, the path tracer samples the surface's reflection or refraction
direction using the **GGX (Trowbridge-Reitz)** microfacet distribution. This
distribution models rough surfaces as a collection of microfacets whose
normals follow a specific probability density.

### 1.1. Sampling a Microfacet Normal

Given two random numbers $u_1, u_2 \in [0, 1)$ and the roughness parameter
$\alpha = Pr^2$ (where $Pr$ is the material roughness), a microfacet normal
$\vec{H}$ is sampled in tangent space:

$$\phi = 2\pi u_1$$

$$\cos\theta = \sqrt{\frac{1 - u_2}{1 + (\alpha^2 - 1)u_2}}$$

$$\sin\theta = \sqrt{1 - \cos^2\theta}$$

The half-vector in tangent space is:

$$\vec{H}_{\text{tangent}} = (\cos\phi \cdot \sin\theta,\; \sin\phi \cdot \sin\theta,\; \cos\theta)$$

### 1.2. Tangent-Space Transform

The half-vector is transformed from tangent space to world space using a
**TBN (Tangent-Bitangent-Normal) frame** built at the hit point:

$$\vec{H}_{\text{world}} = \vec{T} \cdot H_x + \vec{B} \cdot H_y + \vec{N} \cdot H_z$$

where:

- $\vec{T}$ = surface tangent (computed from the geometric normal)
- $\vec{B}$ = surface bitangent (cross product of normal and tangent)
- $\vec{N}$ = surface normal (possibly perturbed by a normal map)

### 1.3. Reflected Direction

The outgoing direction is computed by reflecting the incident ray $\vec{D}$
about the sampled microfacet normal $\vec{H}$:

$$\vec{R} = \text{reflect}(\vec{D}, \vec{H}) = \vec{D} - 2(\vec{D} \cdot \vec{H})\vec{H}$$

### 1.4. Importance Sampling Rationale

GGX importance sampling concentrates samples in the direction of dominant
reflectance (around the specular lobe). This reduces variance compared to
uniform hemisphere sampling, especially for glossy surfaces. The distribution
becomes:

- **Smooth surfaces** ($\alpha \to 0$): samples cluster tightly around the
  perfect reflection direction
- **Rough surfaces** ($\alpha \to 1$): samples spread broadly across the
  hemisphere

---

## 2. Bounce Loop

The path tracer executes up to `MAX_BOUNCE = 4` bounces per pixel, similar to
PBR mode but with GGX-sampled directions.

### 2.1. Through-Power Initialization

The `through_power` starts at:

$$\text{through\_power} = (0.33,\; 0.33,\; 0.33)$$

This is approximately $1/3$ per channel. The 3× compensation (multiplying by 3
at the final skybox accumulation) restores energy while preventing early
oversaturation. This also accounts for the three RGB channels splitting the
wavelength space.

### 2.2. Per-Bounce Flow

```
For bounce = 0 to MAX_BOUNCE - 1:

    1. Cast ray through BVH → nearest hit
    2. If no hit:
         accumulated += skybox * through_power * 3  (3× boost)
         break
    3. path_sample_materials():
       a. Sample textures (normal map, roughness, etc.)
       b. Compute GGX half-vector from random u1,u2
       c. Decide: reflect or refract based on opacity
          - If random > opacity:
              // Refract with dispersion
              GGX-sample refraction direction
              If first refraction (is_diffract):
                  through_power *= rainbow_color()
                  through_power *= 3
              Get IOR modulated by wavelength (dispersion)
          - Else:
              // Reflect with GGX sampling
              reflect direction = reflect(incident, GGX half-vector)
       d. Compute reflectivity from Fresnel + glossy
    4. If material is emissive:
         accumulated += ke * through_power
         return  (terminate path)
    5. accumulated += kd * (1 - reflectivity) * through_power
    6. through_power *= reflectivity
    7. If through_power negligible → break
```

### 2.3. Direct Emissive Lighting

If a ray hits an emissive surface ($k_e > 0$), the path immediately terminates
and the emissive color is added weighted by the current `through_power`:

$$\text{accumulated} += k_e \cdot \text{through\_power}$$

This provides direct lighting from emissive materials — a feature not available
in Phong or PBR modes.

### 2.4. 3× Boost at Skybox

When a ray exits the scene (no hit), the skybox color is added with an extra
3× multiplier:

$$\text{accumulated} += \text{skybox} \cdot \text{through\_power} \cdot 3$$

This compensates for the initial $1/3$ per-channel `through_power` and ensures
the skybox contributes full brightness.

---

## 3. Chromatic Dispersion

The Monte Carlo path tracer implements **chromatic dispersion** — the
wavelength-dependent variation of the index of refraction that causes rainbows
in transparent materials (like a prism or diamond).

### 3.1. Wavelength from Through-Power Color

The path's current `through_power` RGB color is converted to a **hue**
(0–240°, excluding magenta). The hue is mapped to a **spectrum index**
(0–255) which represents a wavelength in the visible spectrum:

$$hue = \text{RGBtoHue}(\text{through\_power})$$

$$\text{spectrum\_index} = \frac{hue}{240^\circ} \times 255$$

$$\text{wavelength\_factor} = \frac{\text{spectrum\_index}}{127.5} - 1$$

### 3.2. IOR Modulation

The material's base IOR is modulated by the wavelength factor:

$$\eta_{\text{modulated}} = \eta_{\text{base}} + \text{wavelength\_factor} \cdot \text{dispersion} \cdot (\eta_{\text{base}} - 1)$$

where `dispersion` is a fixed constant (0.03 in the implementation).

This means:

- **Red wavelengths** (long, low spectrum index) → lower IOR → refract less
- **Blue/violet wavelengths** (short, high spectrum index) → higher IOR →
  refract more

The result: white light entering a transparent material splits into its
constituent colors, just like a real prism.

### 3.3. Rainbow Color on First Refraction

The first time a path refracts through a dispersive material, the
`through_power` is multiplied by a random **rainbow color** and boosted by
3×:

$$\text{through\_power} \mathrel{*}= \text{rainbow\_color}() \times 3$$

The rainbow palette cycles through:

$$Red \to Orange \to Yellow \to Green \to Blue \to Violet$$

This initial color seed determines the wavelength for subsequent dispersion
calculations, establishing the path's "color identity."

---

## 4. Complete Kernel Flow

```
monte_carlo_kernel(pixel_x, pixel_y):
    1. Generate camera ray (with DOF jitter)
    2. through_power = (0.33, 0.33, 0.33)
    3. accumulated = (0, 0, 0)
    4. is_diffract = true

    5. For bounce = 0 to MAX_BOUNCE-1:
        a. Trace BVH → hit or miss
        b. If miss → accumulated += skybox * through_power * 3; break
        c. Sample materials (GGX half-vector, texture lookups)
        d. Compute F0, Fresnel F(θ), glossy, reflectivity
        e. If emissive → accumulated += ke * through_power; break
        f. accumulated += kd * (1 - reflectivity) * through_power
        g. through_power *= reflectivity
        h. If refracting:
             If is_diffract:
                 through_power *= rainbow_color() * 3
                 is_diffract = false
             Modulate Ni by wavelength (dispersion)
             Compute refracted direction (Snell's law with modulated Ni)
           Else:
             Outgoing = reflect(incident, GGX half-vector)
        i. Ray origin = hit_point + epsilon

    6. accu[pixel] += accumulated
```

---

## 5. Material Parameters Used

| Parameter | Monte Carlo Role |
|---|---|
| `Kd` | Diffuse albedo (direct scattering) |
| `Ke` | Emissive color (direct light source) |
| `Ni` | Base index of refraction (modulated by dispersion) |
| `d` | Opacity (reflection vs. refraction + dispersion) |
| `Pr` | Roughness (GGX alpha) |
| `Pm` | Metalness (F0 blending) |
| `map_*` | All texture maps apply |

---

## 6. Performance and Convergence

Monte Carlo mode is the **slowest** mode because:

- 1 sample per pixel per frame (progressive accumulation)
- GGX sampling per bounce
- Texture lookups at each bounce
- Chromatic dispersion calculations

But it produces the **highest quality** results:

- Physically correct light transport (multiple bounces, scattering)
- Soft, realistic reflections (GGX microfacet distribution)
- Chromatic dispersion (rainbow effects in glass/prisms)
- Emissive surfaces act as light sources
- Progressive accumulation converges to ground truth over hundreds of frames