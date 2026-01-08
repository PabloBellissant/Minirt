/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 04:16:00 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/17 04:16:00 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "vec3_special1.h"
#include <float.h>

t_rgb	hit_light_plane(t_ray *ray, t_scene *scene, float t_min, t_mat *mat);
t_rgb	hit_color_bvh(t_ray *ray, t_aabb_bvh *bvh, t_mat *mat, float t_min);

float	rgb_sum(t_rgb rgb)
{
	float	sum;

	sum = rgb.r + rgb.g + rgb.b;
	return (sum);
}

t_rgb	hit_register_light(t_ray *ray, t_scene *scene, float light_distance)
{
	t_rgb		color;

	color = hit_light_plane(ray, scene, light_distance, scene->mat.data);
	if (rgb_sum(color) <= 0.05f)
		return (color);
	color = rgb_mult(color, hit_color_bvh(ray, scene->bvh.aabb_bvh,
				scene->mat.data, light_distance));
	return (color);
}

bool	hit_box(t_ray *ray, t_aabb_bvh *bvh);

t_rgb	hit_color_object(t_ray *ray, t_aabb_bvh *bvh, t_mat *mat, float t_min);

t_rgb	hit_color_bvh(t_ray *ray, t_aabb_bvh *bvh, t_mat *mat, float t_min)
{
	t_rgb		color;

	if (bvh->depth < 2)
		return (hit_color_object(ray, bvh, mat, t_min));
	if (!hit_box(ray, bvh))
		return (rgb(1, 1, 1));
	color = hit_color_bvh(ray, bvh->next_a, mat, t_min);
	color = vec3_mult(color, hit_color_bvh(ray, bvh->next_b, mat, t_min));
	return (color);
}

t_rgb	get_color_2(t_ray *ray, t_aabb_bvh *bvh, t_mat *mat, float t_min)
{
	t_object	*object[2];
	t_rgb		color;

	object[0] = bvh->object_a;
	object[1] = bvh->object_b;
	if (object[0]->f(ray, object[0], &object[0]->t) == 0
		|| object[0]->t > t_min)
	{
		if (object[1]->f(ray, object[1], &object[1]->t) == 0
			|| object[1]->t > t_min)
			return (rgb(1, 1, 1));
		return (rgb_scale(mat[object[1]->mat_id].kd, 1.0f
				- mat[object[1]->mat_id].opacity));
	}
	if (object[1]->f(ray, object[1], &object[1]->t) == 0
		|| object[1]->t > t_min)
		return (rgb_scale(mat[object[0]->mat_id].kd, 1.0f
				- mat[object[0]->mat_id].opacity));
	color = rgb_scale(mat[object[0]->mat_id].kd, 1.0f
			- mat[object[0]->mat_id].opacity);
	color = rgb_mult(color, rgb_scale(mat[object[0]->mat_id].kd, 1.0f
				- mat[object[0]->mat_id].opacity));
	return (color);
}

t_rgb	hit_color_object(t_ray *ray, t_aabb_bvh *bvh, t_mat *mat, float t_min)
{
	t_rgb		color;

	if (bvh->depth == 1)
		return (get_color_2(ray, bvh, mat, t_min));
	if (bvh->depth == 0)
	{
		if (bvh->object_a)
		{
			if (bvh->object_a->f(ray, bvh->object_a, &bvh->object_a->t) == 0)
				return (rgb(1, 1, 1));
		}
		else
			return (rgb(1, 1, 1));
		if (bvh->object_a->t > t_min)
			return (rgb(1, 1, 1));
		return (rgb_scale(mat[bvh->object_a->mat_id].kd, 1.0f
				- mat[bvh->object_a->mat_id].opacity));
	}
	color = hit_color_object(ray, bvh->next_a, mat, t_min);
	color = vec3_mult(color, hit_color_object(ray, bvh->next_b, mat, t_min));
	return (color);
}
