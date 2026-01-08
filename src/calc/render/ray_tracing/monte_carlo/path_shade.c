/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_shade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:55:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 01:44:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "calc.h"
#include "object.h"
#include "parsing.h"
#include <X11/Xutil.h>
#include "calc.h"

#define LIGHT_MULT 50

t_rgb	get_color_through_object(
			t_ray *ray, t_scene *scene, float light_distance);
t_vec3	vec3_inv(t_vec3 vec);
t_rgb	hit_register_light(t_ray *ray, t_scene *scene, float light_distance);
t_rgb	get_color_through(t_data *data, t_vec3 hit_point,
			t_vec3 to_light);
t_rgb	get_diffuse(t_rgb hit_rgb, t_vec3 reflect);
float	rgb_luminance(t_rgb color);

static t_rgb	send_ray_to_light(
			t_vec3 orig, t_vec3 dir, t_scene *scene, float t)
{
	t_ray	temp;

	temp.origin = orig;
	temp.dir = dir;
	temp.inv_dir = vec3_inv(dir);
	return (hit_register_light(&temp, scene, t));
}

static t_rgb	fill_monte_carlo(t_hit *hit, t_scene *scene, int emissive_count)
{
	t_rgb	color_through;
	t_light	light;
	float	distance;
	t_vec3	to_light;
	t_rgb	diffuse;

	light = get_random_light(scene, emissive_count, hit->hit_point);
	to_light = vec3_sub(light.pos, hit->hit_point);
	distance = vec3_length2(to_light);
	to_light = vec3_normalize(to_light);
	diffuse = get_diffuse(hit->hit_rgb, hit->reflectivity);
	color_through = send_ray_to_light(
			hit->hit_point, to_light, scene, sqrtf(distance));
	light.rgb = rgb_mult(light.rgb, color_through);
	light.rgb = rgb_scale(light.rgb, LIGHT_MULT / distance);
	light.rgb = rgb_mult(diffuse, light.rgb);
	distance = fmaxf(0.0f, vec3_dot(to_light, hit->normal));
	light.rgb = rgb_scale(light.rgb, distance * emissive_count);
	light.rgb = rgb_add(light.rgb, rgb_mult(diffuse, scene->ambient));
	return (light.rgb);
}

void	path_shade(t_buffers *buffers, int pixel, t_scene *scene)
{
	t_rgb	color;
	int		count;

	count = scene->lights.num_elements + scene->emissive_count;
	if (count > 0)
	{
		color = fill_monte_carlo(&buffers->hits[pixel], scene, count);
		color = rgb_add(buffers->hits[pixel].ke, color);
		color = rgb_clamp(color, 0.0f, 1.0f);
		color = rgb_mult(
				color, buffers->rays[buffers->hits[pixel].id].through_power);
		buffers->rays[buffers->hits[pixel].id].accumulated_color
			= rgb_add(buffers->rays[buffers->hits[pixel].id].accumulated_color,
				color);
	}
	buffers->rays[buffers->hits[pixel].id].through_power
		= vec3_mult(buffers->rays[buffers->hits[pixel].id].through_power,
			buffers->hits[pixel].reflectivity);
}

t_rgb	get_diffuse(t_rgb hit_rgb, t_vec3 reflect)
{
	t_rgb	diffuse;

	diffuse = rgb_mult(
			hit_rgb, vec3(1 - reflect.r, 1 - reflect.g, 1 - reflect.b));
	diffuse = rgb_scale(diffuse, 1.0f / M_PI);
	return (diffuse);
}

void	path_shade_loop(t_buffers *buffers, t_scene *scene, int count)
{
	int			pixel;

	pixel = 0;
	while (pixel < count)
	{
		path_shade(buffers, pixel, scene);
		++pixel;
	}
}
