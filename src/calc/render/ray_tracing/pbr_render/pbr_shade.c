/* **********************l*************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:55:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 01:44:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_types.h"
#include "minirt.h"
#include "calc.h"
#include "mlx_draw.h"
#include "rgb_operations.h"
#include "vec3_operations.h"
#include "vec3_special1.h"
#include "vec3_special2.h"

static t_vec3	reflection(const t_vec3 normal, const t_vec3 light_dir)
{
	const float	r = vec3_dot(light_dir, normal) * 2;

	return (vec3_sub(vec3_scale(normal, r), light_dir));
}

static t_rgb	get_diffuse(const t_vec3 l_m, const t_rgb i_d, const t_vec3 n, const t_vec3 k_d)
{
	const float	surface_faces_light = vec3_dot(l_m, n);

	if (surface_faces_light <= 0)
		return (rgb(0, 0, 0));
	return (vec3_scale(vec3_mult(k_d, i_d), surface_faces_light));
}

static t_rgb	get_specular(const t_vec3 r_m, const t_vec3 v, t_vec3 k_s, const float n_s)
{
	float	surface_faces_camera;

	surface_faces_camera = vec3_dot(r_m, v);
	if (surface_faces_camera <= 0)
		return (rgb(0, 0, 0));
	surface_faces_camera = powf(surface_faces_camera, n_s);
	return (vec3_scale(k_s, surface_faces_camera));
}

t_rgb	get_color_through_object(t_ray *ray, t_scene *scene, float light_distance);

t_vec3	vec3_inv(t_vec3 vec);

t_rgb	hit_register_light(t_ray *ray, t_scene *scene, float light_distance);

t_rgb	get_color_through(t_data *data, t_vec3 hit_point,
		t_vec3 to_light)
{
	t_ray			ray;
	t_rgb			color_through;

	ray.origin = hit_point;
	ray.dir = vec3_normalize(to_light);
	ray.inv_dir = vec3_inv(ray.dir);
	color_through = hit_register_light(&ray, &data->scene, vec3_length(to_light));
	return (color_through);
}

void	shade(t_buffers *buffers, int pixel, t_scene *scene, t_data *data)
{
	t_object	*lights;
	size_t		m;
	t_vec3		dir_to_cam;
	t_vec3		light_reflect_dir;
	t_vec3		dir_to_light;

	lights = scene->lights.data;
	dir_to_cam = vec3_normalize(vec3_sub(scene->camera.pos, buffers->hits[pixel].hit_point));
	const t_rgb	ambient = vec3_mult(buffers->hits[pixel].hit_rgb,
							  vec3_scale(scene->ambient, buffers->hits[pixel].hit_ambient));
	t_rgb		diffuse_m;
	t_rgb		specular_m;
	t_rgb		color_through;
	t_rgb		color;
	t_rgb		receive_color;
	color = rgb(0, 0, 0);
	m = 0;
	while (m < scene->lights.num_elements)
	{
		dir_to_light = vec3_sub(lights[m].light.pos, buffers->hits[pixel].hit_point);	
		color_through = get_color_through(data, buffers->hits[pixel].hit_point, dir_to_light);
		receive_color = rgb_mult(lights[m].light.rgb, color_through);
		dir_to_light =  vec3_normalize(dir_to_light);
		diffuse_m = get_diffuse(dir_to_light, receive_color,
				buffers->hits[pixel].normal, buffers->hits[pixel].hit_rgb);
		light_reflect_dir = reflection(buffers->hits[pixel].normal, dir_to_light);
		specular_m = get_specular(light_reflect_dir, dir_to_cam, buffers->hits[pixel].ks, buffers->hits[pixel].ns);
		specular_m = rgb_mult(specular_m, receive_color);
		color = vec3_add(color, vec3_add(diffuse_m, specular_m));
		m++;
	}
	color = vec3_add(vec3_add(color, ambient), buffers->hits[pixel].ke);
	color = rgb_mult(color, buffers->rays[buffers->hits[pixel].id].through_power);
	color = rgb_mult(color, vec3_sub(vec3(1, 1, 1), buffers->hits[pixel].reflectivity));
	buffers->rays[buffers->hits[pixel].id].accumulated_color = rgb_add(buffers->rays[buffers->hits[pixel].id].accumulated_color, color);
	buffers->rays[buffers->hits[pixel].id].through_power = vec3_mult(buffers->rays[buffers->hits[pixel].id].through_power, buffers->hits[pixel].reflectivity);
}

void	shade_loop(t_buffers *buffers, t_scene *scene, t_data *data, int count)
{
	int			pixel;

	pixel = 0;
	while (pixel < count)
	{
		shade(buffers, pixel, scene, data);
		++pixel;
	}
}


