/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:48:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/19 23:37:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "vectors.h"
#include "calc.h"

#define OFFSET 0.001f

static void	hit_register_obj(t_ray *restrict ray,
	t_object *restrict objects, float t_min)
{
	t_vec3	hit_dir;
	t_vec3	hit_point;

	hit_dir = vec3_scale(ray->dir, t_min);
	hit_point = vec3_add(ray->pos, hit_dir);
	if (objects->type == SPHERE)
	{
		ray->hit_normal = vec3_sub(hit_point, objects->sphere.pos);
		ray->hit_rgb = objects->sphere.rgb;
	}
	else if (objects->type == PLANE)
	{
		ray->hit_normal = objects->plane.normal;
		ray->hit_rgb = objects->plane.rgb;
	}
	else
	{
		ray->hit_normal = vec3_sub(hit_point, objects->cylinder.pos);
		ray->hit_rgb = objects->cylinder.rgb;
	}
	ray->hit_normal = vec3_normalize(ray->hit_normal);
	ray->pos = hit_point;
}

float	hit_register(t_ray *restrict ray, t_scene *scene)
{
	t_object	*object;
	t_object	*bvh_ret;

	object = hit_reg_plane(ray, scene);
	bvh_ret = hit_bvh(ray, scene->bvh);
	if (bvh_ret != NULL)
	{
		if (!object || bvh_ret->t < object->t)
			object = bvh_ret;
	}
	else if (!object || object->t == FLT_MAX)
		return (0);
	hit_register_obj(ray, object, object->t);
	return (object->t);
}
