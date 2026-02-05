// vim: ft=c

# include "include/gpu.cl"

__kernel void	normal_debug(t_camera_gpu cam, __constant t_sphere_gpu *spheres, __constant t_bvh_gpu *sphere_bvh, __constant t_triangle_gpu *triangles, __constant t_bvh_gpu *triangle_bvh, __constant t_plane_gpu *planes, int planes_count, __global float3 *img, __constant uchar *textures, __constant t_mat_gpu *mats)
{
	int2		pos;
	t_ray_gpu	ray;
	int			pixel;
	t_hit_gpu	hit;
	t_objects	objects;	

	objects.spheres = spheres;
	objects.sphere_bvh = sphere_bvh;
	objects.triangles = triangles;
	objects.triangle_bvh = triangle_bvh;
	objects.planes = planes;
	objects.planes_count = planes_count;
	pos.x = get_global_id(0);
	pos.y = get_global_id(1);
	if (pos.x >= (int) get_global_size(0) || pos.y >= (int) get_global_size(1))
		return ;
	pixel = pos.y * get_global_size(0) + pos.x;
	uint		rng = cam.frame * get_global_size(1) * get_global_size(0) + pixel;
	ray = calc_ray(&cam, pos, &rng);
	hit = hit_register_gpu(&ray, &objects);
	if (hit.hit_obj > -1)
	{
		t_hit_data	hit_data = sample_materials(&hit, textures, mats, &ray);
		img[pixel] += hit_data.normal * 0.5f + 0.5f;
	}
	else
		img[pixel] = 0;
}
