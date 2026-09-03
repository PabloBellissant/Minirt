// vim: ft=c

#include "include/gpu.cl"

static float3	get_tangent(float3 n)
{
	float3	up;

	if (fabs(n.y) > 0.999f)
		up = (float3)(1, 0, 0);
	else
		up = (float3)(0, 1, 0);
	return (normalize(cross(up, n)));
}

static float3	apply_normal_map(float3 normal, float3 nmap, 
	float3 tangent, float3 bitangent)
{
    float3	world_normal;
	float3	n;

	n = nmap * 2.0f - 1.0f;
	world_normal = (tangent * n.x) + (bitangent * -n.y) + (normal * n.z);
    return (normalize(world_normal));
}

rgb3	get_f0(float metalness, float ior, rgb3 ks)
{
	float	no_metal;

	no_metal = ((ior - 1.0f) / (ior + 1.0f));
	no_metal *= no_metal;
	return (mix((float3)no_metal, ks, metalness));
}

float3	get_reflect(float3 ray_dir, float3 normal, float roughness, float3 F0)
{
	float3	fresnel;
	float	cos_theta;
	float	glossy_factor;
	float3	specular;

	cos_theta = fabs(dot(ray_dir, normal));
	fresnel = (1 - F0) * (pow(1.0f - cos_theta, 5.0f));
	fresnel += F0;
	glossy_factor = 1.0f - (roughness * roughness);
	specular = fresnel * glossy_factor;
	return (clamp(specular, 0.0f, 1.0f));
}

t_hit_data	sample_materials(__private t_hit_gpu *hit, __constant uchar *tex, __constant t_mat_gpu *mat, __private t_ray_gpu *ray)
{
	float3		tangent;
	float3		bitangent;
	rgb3		nmap;
	t_hit_data	hit_data;
	rgb3		f0;

	hit_data.kd = sample_texture(tex, hit->uv, &mat[hit->mat_id].kd_id);
	hit_data.ambient = sample_gray_level_texture(tex,
				hit->uv, &mat[hit->mat_id].ambient_id);
	hit_data.ks = mat[hit->mat_id].ks;
	hit_data.ke = mat[hit->mat_id].ke;
	hit_data.ns = mat[hit->mat_id].ns;
	nmap = sample_texture(tex, hit->uv, &mat[hit->mat_id].normal_id);
	tangent = get_tangent(hit->normal);
	bitangent = cross(hit->normal, tangent);
	hit_data.normal = apply_normal_map(hit->normal, nmap, tangent, bitangent);
	hit_data.metalness = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].metalness_id);
	hit_data.roughness = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].roughness_id);
	hit_data.opacity = sample_gray_level_texture(tex, hit->uv, &mat[hit->mat_id].opacity_id);
	f0 = get_f0(hit_data.metalness, mat[hit->mat_id].ni, hit_data.ks);
	hit_data.reflectivity = get_reflect(ray->dir, hit_data.normal, hit_data.roughness, f0);
	hit_data.ni = mat[hit->mat_id].ni;
	return (hit_data);
}

float3	vec3_refract(float3 ray_dir, float3 normal, float eta)
{
	float	cosi;
	float	cost2;
	float	cost;
	float3	refract_dir;

	cosi = -dot(ray_dir, normal);
	cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (cost2 < 0.0001f)
		return ((float3) (0, 0, 0));
	cost = sqrt(cost2);
	refract_dir = ray_dir * eta + normal * (eta * cosi - cost);
	return (normalize(refract_dir));
}

float3	reflect(float3 dir, float3 normal);

int	refract(float3 *dir, t_hit_gpu *hit, t_hit_data *hit_data, float ni)
{
	float	cos_theta;
	float3	new_dir;
	float3	normal;

	if (hit->hit_type != PLANE)
	{
		normal = hit_data->normal;
		cos_theta = dot(*dir, normal);
		if (cos_theta < 0.0f)
			new_dir = vec3_refract(*dir, hit_data->normal, 1.0f / ni);
		else
			new_dir = vec3_refract(*dir, hit_data->normal * -1, ni);
		if (dot(new_dir, new_dir) < 0.0001f)
			*dir = reflect(*dir, hit_data->normal);
		else
			*dir = new_dir;
	}
	return (0);
}

t_hit_data	sample_refract(__private t_hit_gpu *hit, __constant uchar *tex, __constant t_mat_gpu *mat, __private t_ray_gpu *ray, float random)
{
	t_hit_data	hit_data;

	hit_data = sample_materials(hit, tex, mat, ray);
	hit_data.opacity = fmax(hit_data.opacity, hit_data.reflectivity.x);
	if (random > hit_data.opacity)
	{
		refract(&ray->dir, hit, &hit_data, hit_data.ni);
		hit_data.reflectivity = 1 - hit_data.opacity;
	}
	else
		ray->dir = reflect(ray->dir, hit->normal);
	ray->origin = hit->hit_point + (0.0001f * ray->dir);
	ray->inv_dir = 1 / ray->dir; 
	return (hit_data);
}

float randomf(uint *rng);
float3	sample_ggx_gpu(float3 normal, float roughness, uint *rng)
{
	float	a;
	float	u1;
	float	u2;
	float	phi;
	float	cos_theta;
	float	sin_theta;
	float3	h;
	float3	t;
	float3	b;

	if (roughness <= 0.001f)
		return (normal);
	a = roughness * roughness;
	u1 = randomf(rng);
	u2 = randomf(rng);
	phi = 2.0f * M_PI * u1;
	cos_theta = sqrt((1.0f - u2) / (1.0f + (a * a - 1.0f) * u2));
	sin_theta = sqrt(1.0f - cos_theta * cos_theta);
	h = (float3)(cos(phi) * sin_theta, sin(phi) * sin_theta, cos_theta);
	t = get_tangent(normal);
	b = cross(normal, t);
	h = normalize(t * h.x + b * h.y + normal * h.z);
	return (h);
}

int rgb_to_spectrum_index(float3 rgb)
{
    float max_c = fmax(fmax(rgb.x, rgb.y), rgb.z);
    float min_c = fmin(fmin(rgb.x, rgb.y), rgb.z);
    float delta = max_c - min_c;
    float hue;
    
    if (max_c == rgb.x)
        hue = 60.0f * fmod((rgb.y - rgb.z) / delta + 6.0f, 6.0f);
    else if (max_c == rgb.y)
        hue = 60.0f * ((rgb.z - rgb.x) / delta + 2.0f);
    else
        hue = 60.0f * ((rgb.x - rgb.y) / delta + 4.0f);
    return hue;
}

float get_ni_by_color(float ni_base, float3 rgb, float dispersion)
{
    int		spectrum_index;
    float	wavelength_factor;
    float	dispersion_scale;

    spectrum_index = rgb_to_spectrum_index(rgb);
    wavelength_factor = (spectrum_index / 127.5f) - 1.0f;
    dispersion_scale = ni_base - 1.0f;
    return (ni_base + wavelength_factor * dispersion * dispersion_scale);
}


float3 rainbow_color(uint *rng)
{
	return (normalize((float3) (randomf(rng), randomf(rng), randomf(rng))));
}

t_hit_data path_sample_materials(__private t_hit_gpu *hit, __constant uchar *tex,
                                 __constant t_mat_gpu *mat, __private t_ray_gpu *ray, __private uint *rng, __private float3 *through_power, __private int *is_diffract)
{
	t_hit_data	hit_data;

	hit_data = sample_materials(hit, tex, mat, ray);
	hit_data.opacity = fmax(hit_data.opacity, hit_data.reflectivity.x);
	if (randomf(rng) > hit_data.opacity)
	{
		ray->dir = sample_ggx_gpu(ray->dir, hit_data.roughness, rng);
		if (*is_diffract == 0)
		{
			*is_diffract = 1;
			*through_power *= rainbow_color(rng) * 3;
		}
		refract(&ray->dir, hit, &hit_data, get_ni_by_color(hit_data.ni, *through_power, 0.1));
	}
	else
		ray->dir = reflect(ray->dir, sample_ggx_gpu(hit_data.normal, hit_data.roughness, rng));
	ray->origin = hit->hit_point + (0.0001f * ray->dir);
	ray->inv_dir = 1 / ray->dir; 
	return (hit_data);
}
