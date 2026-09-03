// vim: ft=c

#include "include/gpu.cl"

__kernel void	phong(t_camera_gpu cam,
					__constant t_bvh_node_gpu *bvh,
					int bvh_type,
					__constant t_sphere_gpu *spheres,
					__constant t_triangle_gpu *triangles,
					__constant t_plane_gpu *planes,
					int planes_count,
					__global float3 *img,
					__constant uchar *textures,
					__constant t_mat_gpu *mats,
					__constant t_light_gpu *lights,
					int lights_count,
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
	pixel = pos.y * get_global_size(0) + pos.x;
	uint		rng = cam.frame * get_global_size(1) * get_global_size(0) + pixel;
	ray = calc_ray(&cam, pos, &rng);
	hit = hit_register_gpu(&ray, &objects, bvh_type);
	if (hit.hit_obj > -1)
	{
		t_hit_data	hit_data = sample_materials(&hit, textures, mats, &ray);
		hit_data.kd = phong_shading(&hit_data, &hit, &ray, &objects, ambient, bvh_type); 
		img[pixel] += hit_data.kd; 
	}
	else
		img[pixel] = 0;
}

