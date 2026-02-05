// vim: ft=c

# include "include/gpu.cl"

rgb3	get_phong_diffuse(rgb3 l_m, rgb3 i_d, rgb3 n, rgb3 k_d)
{
	const float	surface_faces_light = dot(l_m, n);

	if (surface_faces_light <= 0)
		return ((rgb3) (0, 0, 0));
	return ((k_d * i_d) *  surface_faces_light);
}

rgb3	get_specular(rgb3 r_m, rgb3 v, rgb3 k_s, float n_s)
{
	float	surface_faces_camera;

	surface_faces_camera = dot(r_m, v);
	if (surface_faces_camera <= 0)
		return ((rgb3)(0, 0, 0));
	surface_faces_camera = pow(surface_faces_camera, n_s);
	return (k_s * surface_faces_camera);
}

rgb3	reflection(rgb3 normal, rgb3 light_dir)
{
	const float	r = dot(light_dir, normal) * 2;

	return ((normal * r) - light_dir);
}

rgb3	get_color_through(float3 pos, float3 dir, __private t_objects *objects, float light_length2)
{
	t_ray_gpu	ray;
	t_hit_gpu	hit;

	ray.origin = pos;
	ray.dir = dir;
	ray.inv_dir = 1.0f / dir;
	hit = hit_register_gpu(&ray, objects);
	if (hit.hit_obj == -1 || dot(hit.hit_point - pos, hit.hit_point - pos) > light_length2)
		return ((rgb3) (1, 1, 1));
	return ((rgb3) (0, 0, 0));
}

rgb3	phong_shading(__private t_hit_data *hit_data, __private t_hit_gpu *hit, __private t_ray_gpu *ray, __private t_objects *objects, rgb3 ambient)
{
	int		i;
	float3	dir_to_light;
	rgb3	color = ambient;
	rgb3	receive_color;
	rgb3	diffuse;
	rgb3	specular;
	rgb3	light_reflect;
	float3	dir_to_cam;
	float3	hit_point;

	hit_point = hit->hit_point + (hit->normal * 0.00001f);
	color *= hit_data->kd;
	dir_to_cam = normalize(ray->origin - hit->hit_point);
	i = 0;
	while (i < objects->lights_count)
	{
		dir_to_light = normalize(objects->lights[i].pos - hit_point);
		receive_color = objects->lights[i].rgb * get_color_through(hit_point, dir_to_light, objects, dot(hit_point - objects->lights[i].pos, hit_point - objects->lights[i].pos));
		diffuse = get_phong_diffuse(dir_to_light, receive_color, hit_data->normal, hit_data->kd); 
		light_reflect = reflection(hit_data->normal, dir_to_light); 
		specular = get_specular(light_reflect, dir_to_cam, hit_data->ks, hit_data->ns) * receive_color;
		color += diffuse + specular;
		++i;
	}
	color += hit_data->ke;
	color = clamp(color, 0.0f, 1.0f);
	return (color);
}
