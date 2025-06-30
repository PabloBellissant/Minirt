/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:48:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/29 04:48:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"
#include "bvh.h"
#include "calc.h"

bool	hit_box(t_ray *ray, t_bvh *bvh);
void	get_t(t_ray *ray, t_object *object, float *t);

inline t_object	*hit_bvh(t_ray *ray, t_bvh *bvh)
{
	t_object	*object_a;
	t_object	*object_b;
	float		object_a_t;
	float		object_b_t;

	if (bvh->depth == 0)
		return (bvh->object);
	object_a_t = NAN;
	object_b_t = NAN;
	if (hit_box(ray, bvh->next_a) == true)
	{
		object_a = hit_bvh(ray, bvh->next_a);
		get_t(ray, object_a, &object_a_t);
	}
	if (hit_box(ray, bvh->next_b) == true)
	{
		object_b = hit_bvh(ray, bvh->next_b);
		get_t(ray, object_b, &object_b_t);
	}
	if (isnan(object_a_t))
	{
		if (isnan(object_b_t))
			return (NULL);
		return (object_b);
	}
	if (isnan(object_b_t) || object_b_t > object_a_t)
		return (object_a);
	return (object_b);
}

void	get_t(t_ray *ray, t_object *object, float *t)
{
	if (object->type == PLANE)
	{
		if (hit_plane(ray, &object->plane, t) == 0)
			*t = NAN;
		return ;
	}
	if (object->type == SPHERE)
	{
		if (hit_sphere(ray, &object->sphere, t) == 0)
			*t = NAN;
		return ;
	}
	if (object->type == TRIANGLE)
	{
		if (hit_triangle(ray, &object->triangle, t) == 0)
			*t = NAN;
		return ;
	}
	if (object->type == CYLINDER)
	{
		if (hit_cylinder(ray, &object->cylinder, t) == 0)
			*t = NAN;
		return ;
	}
	*t = NAN;
}

// inline void	swap_float(float *a, float *b)
// {
// 	float	temp;
//
// 	temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

inline bool hit_box(t_ray *ray, t_bvh *bvh)
{
	float t_min = -INFINITY;
	float t_max = INFINITY;
	int i = 0;

	while (i < 3)
	{
		float ray_origin = ((float *)&ray->pos)[i];
		float ray_dir = ((float *)&ray->dir)[i];
		float box_min = ((float *)&bvh->pos)[i];
		float box_max = box_min + ((float *)&bvh->size)[i];

		if (fabsf(ray_dir) < 1e-8f)
		{
			if (ray_origin < box_min || ray_origin > box_max)
				return false;
		}
		else
		{
			float t1 = (box_min - ray_origin) / ray_dir;
			float t2 = (box_max - ray_origin) / ray_dir;
			if (t1 > t2)
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}
			if (t1 > t_min)
				t_min = t1;
			if (t2 < t_max)
				t_max = t2;
			if (t_min > t_max)
				return false;
		}
		i++;
	}
	return (t_max >= 0);
}

