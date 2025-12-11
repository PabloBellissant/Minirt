/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shadow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 07:11:21 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/04 07:11:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "minirt.h"

t_shadow_ray	cast_shadow_rays(t_hit *hits, int pixel, t_object *light);

void	intersect_shadow(t_hit *hits, t_light_result *results, t_scene *scene, int pixel)
{
	t_object		*bvh_hit;
	t_object		*plane_hit;
	size_t			i;
	t_object		*lights;
	t_rgb			color;
	t_shadow_ray	shadow;

	lights = scene->lights.data;
	color = rgb(0, 0, 0);
	i = 0;
	while (i < scene->lights.num_elements)
	{
		shadow = cast_shadow_rays(hits, pixel, lights + i);
		bvh_hit = hit_aabb_bvh(&shadow.ray, scene->bvh.aabb_bvh);
		if (bvh_hit && bvh_hit->t < shadow.light_distance)
		{
			color = vec3_add(color, rgb(0, 0, 0));
		}
		else
		{
			plane_hit = hit_reg_plane(&shadow.ray, scene, shadow.light_distance);
			if (!plane_hit)
				color = vec3_add(color, rgb(1, 1, 1));
		}
		++i;
	}
	results[pixel].color_through = color;
}

t_shadow_ray	cast_shadow_rays(t_hit *hits, int pixel, t_object *light)
{
	t_shadow_ray	shadow;

	shadow.ray.origin = hits[pixel].hit_point;
	shadow.ray.dir = vec3_sub(light->light.pos, hits[pixel].hit_point);
	shadow.light_distance = vec3_length(shadow.ray.dir);
	shadow.ray.dir = vec3_div_scalar(shadow.ray.dir, shadow.light_distance);
	return (shadow);
}

// void	intersect_shadow(t_shadow_ray *shadows, t_shadow_result *results, t_scene *scene, int pixel)
// {
// 	t_object	*bvh_hit;
// 	t_object	*plane_hit;
//
// 	results[pixel].hit_id = shadows[pixel].hit_id;
// 	results[pixel].light_id = shadows[pixel].light_id;
// 	bvh_hit = hit_aabb_bvh(&shadows[pixel].ray, scene->bvh.aabb_bvh);
// 	if (bvh_hit && bvh_hit->t < shadows[pixel].light_distance)
// 	{
// 		results[pixel].color_through = rgb(0, 0, 0);
// 	}
// 	else
// 	{
// 		plane_hit = hit_reg_plane(&shadows[pixel].ray, scene, shadows[pixel].light_distance);
// 		if (plane_hit)
// 			results[pixel].color_through = rgb(0, 0, 0);
// 		else
// 			results[pixel].color_through = rgb(1, 1, 1);;
// 	}
// }
