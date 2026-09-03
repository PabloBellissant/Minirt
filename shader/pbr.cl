// vim: ft=c

#include "include/gpu.cl"

float3	reflect(float3 dir, float3 normal)
{
	float3	scaled_normal;

	scaled_normal = normal * (2 * dot(dir, normal));
	return (dir - scaled_normal);
}

float3	draw_skybox(t_hit_gpu *hit, __constant uchar *textures, t_texture_data skybox) 
{
	int		x;
	int		y;
	uchar3	color;
	int		offset;

	x = (int)(hit->uv.x * (float)(skybox.width - 1));
	y = (int)(hit->uv.y * (float)(skybox.height - 1));
	offset = skybox.offset;
	offset += y * (skybox.width * skybox.channels) + x * skybox.channels;
	color.x = textures[offset];
	color.y = textures[offset + 1];
	color.z = textures[offset + 2];
	return ((rgb3) (color.x / 255.0f, color.y / 255.0f, color.z / 255.0f));
}

__kernel void	pbr(
		t_camera_gpu cam,
		__constant t_bvh_node_gpu *bvh,
		int	bvh_type,
		__constant t_sphere_gpu *spheres,
		__constant t_triangle_gpu *triangles,
		__constant t_plane_gpu *planes,
		int planes_count,
		__global float3 *img,
		__constant uchar *textures,
		__constant t_mat_gpu *mats,
		__constant t_light_gpu *lights,
		int lights_count,
		t_texture_data skybox,
		rgb3 ambient)
{
	int2		pos;
	t_objects	objects;	

	objects.spheres = spheres;
	objects.triangles = triangles;
	objects.bvh = bvh;
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
	float3		accumulated_color;
	float3		through_power;
	accumulated_color = (rgb3)(0, 0, 0);
	through_power = (rgb3)(1, 1, 1);
	pixel = pos.y * get_global_size(0) + pos.x;
	uint		rng = cam.frame * get_global_size(1) * get_global_size(0) + pixel;
	ray = calc_ray(&cam, pos, &rng);
	bounce = 0;
	float	random;
	while (bounce < MAX_BOUNCE)
	{
		hit = hit_register_gpu(&ray, &objects, bvh_type);
		if (hit.hit_obj > -1)
		{
			if (cam.frame == 1)
				random = 1;
			else
				random = randomf(&rng);
			hit_data = sample_refract(&hit, textures, mats, &ray, random);
			accumulated_color += (phong_shading(&hit_data, &hit, &ray, &objects, ambient, bvh_type) * (1 - hit_data.reflectivity)) * through_power; 
			through_power *= hit_data.reflectivity;
		}
		else
		{
			accumulated_color += draw_skybox(&hit, textures, skybox) * through_power;
			break;
		}
		++bounce;
	}
	img[pixel] += accumulated_color;
}

