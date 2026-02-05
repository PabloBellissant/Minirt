// vim: ft=c

# include "include/gpu.cl"


float3	draw_skybox(t_hit_gpu *hit, __constant uchar *textures, t_texture_data skybox);
float3	reflect(float3 dir, float3 normal);
t_hit_data	path_sample_materials(__private t_hit_gpu *hit, __constant uchar *tex, __constant t_mat_gpu *mat, __private t_ray_gpu *ray, __private uint *rng, __private float3 *through_power, __private int *is_diffract);

float3	sample_ggx_gpu(float3 normal, float roughness, uint *rng);
static float3	get_tangent(float3 n);

float randomf(uint *rng)
{
    *rng = *rng * 747796405 + 2891336453;
    uint result = ((*rng >> ((*rng >> 28) + 4)) ^ *rng) * 277803737;
    result = (result >> 22) ^ result;
    return (result / 4294967295.0f);
}

uint	hash(uint x);
__kernel void	monte_carlo(
		t_camera_gpu cam,
		__constant t_sphere_gpu *spheres,
		__constant t_bvh_gpu *sphere_bvh,
		__constant t_triangle_gpu *triangles,
		__constant t_bvh_gpu *triangle_bvh,
		__constant t_plane_gpu *planes,
		int planes_count,
		__global float3 *img,
		__constant uchar *textures,
		__constant t_mat_gpu *mats,
		__constant t_light_gpu *lights,
		int lights_count,
		t_texture_data skybox,
		int random)
{
	int2		pos;
	t_objects	objects;	

	objects.spheres = spheres;
	objects.sphere_bvh = sphere_bvh;
	objects.triangles = triangles;
	objects.triangle_bvh = triangle_bvh;
	objects.planes = planes;
	objects.planes_count = planes_count;
	objects.lights = lights;
	objects.lights_count = lights_count;
	pos.x = get_global_id(0);
	pos.y = get_global_id(1);
	if (pos.x >= (int) get_global_size(0) || pos.y >= (int) get_global_size(1))
		return ;
	t_ray_gpu	ray;
	int			pixel;
	t_hit_gpu	hit;
	t_hit_data	hit_data;
	int			bounce;
	rgb3		accumulated_color;
	rgb3		final_color;
	rgb3		through_power;
	int			is_diffract;

	accumulated_color = (rgb3)(0, 0, 0);
	final_color = (rgb3)(0, 0, 0);
	through_power = (rgb3)(0.33, 0.33, 0.33);

	pixel = pos.y * get_global_size(0) + pos.x;
	uint		rng = random + pixel;
	ray = calc_ray(&cam, pos, &rng);
	is_diffract = 0;
	bounce = 0;
	while (bounce < MAX_BOUNCE)
	{
		hit = hit_register_gpu(&ray, &objects);
		if (hit.hit_obj < 0)
		{
			if (bounce == 0)
				img[pixel] += draw_skybox(&hit, textures, skybox);
			else
				img[pixel] += draw_skybox(&hit, textures, skybox) * accumulated_color * 3;
			return ;
		}
		hit_data = path_sample_materials(&hit, textures, mats, &ray, &rng, &through_power, &is_diffract);
		if (dot(hit_data.ke, hit_data.ke) > 0.0f)
		{
			accumulated_color += hit_data.ke * through_power;
			final_color = accumulated_color * hit_data.ke * 3;
			img[pixel] += final_color;
			return ;
		}
		accumulated_color += (hit_data.kd * (1 - hit_data.reflectivity)) * through_power;
		through_power *= hit_data.reflectivity;
		++bounce;
	}
}

// __kernel void	monte_carlo(
// 		t_camera_gpu cam,
// 		__constant t_sphere_gpu *spheres,
// 		__constant t_bvh_gpu *sphere_bvh,
// 		__constant t_triangle_gpu *triangles,
// 		__constant t_bvh_gpu *triangle_bvh,
// 		__constant t_plane_gpu *planes,
// 		int planes_count,
// 		__global float3 *img,
// 		__constant uchar *textures,
// 		__constant t_mat_gpu *mats,
// 		__constant t_light_gpu *lights,
// 		int lights_count,
// 		t_texture_data skybox,
// 		__constant t_emissive *emissive,
// 		int emissive_count)
// {
// 	int2		pos;
// 	t_objects	objects;	
//
// 	objects.spheres = spheres;
// 	objects.sphere_bvh = sphere_bvh;
// 	objects.triangles = triangles;
// 	objects.triangle_bvh = triangle_bvh;
// 	objects.planes = planes;
// 	objects.planes_count = planes_count;
// 	objects.lights = lights;
// 	objects.lights_count = lights_count;
// 	objects.mats = mats;
// 	pos.x = get_global_id(0);
// 	pos.y = get_global_id(1);
// 	if (pos.x >= (int) get_global_size(0) || pos.y >= (int) get_global_size(1))
// 		return ;
// 	t_ray_gpu	ray;
// 	int			pixel;
// 	t_hit_gpu	hit;
// 	t_hit_data	hit_data;
// 	int			bounce;
// 	rgb3		through_power;
// 	rgb3		final_color;
//
// 	through_power = (rgb3)(1, 1, 1);
// 	final_color = (rgb3)(0, 0, 0);
//
// 	pixel = pos.y * get_global_size(0) + pos.x;
// 	ray = calc_ray(&cam, pos);
// 	bounce = 0;
//
// 	while (bounce < MAX_BOUNCE)
// 	{
// 		hit = hit_register_gpu(&ray, &objects);
// 		if (hit.hit_obj < 0)
// 			break;
//
// 		int	seed = pixel + bounce * 9781u + cam.frame * 6271u;
// 		hit_data = path_sample_materials(&hit, textures, mats);
//
// 		if (dot(hit_data.ke, hit_data.ke) > 0.0f)
// 		{
// 			final_color += through_power * hit_data.ke;
// 			break;
// 		}
// 		final_color += path_shade(&hit, &hit_data, emissive_count, seed, objects);
// 		ray.origin = hit.hit_point + 0.0001f * ray.dir;
// 		ray.inv_dir = 1.0f / ray.dir;
// 		++bounce;
// 	}
//
// 	img[pixel] += final_color;
// }
