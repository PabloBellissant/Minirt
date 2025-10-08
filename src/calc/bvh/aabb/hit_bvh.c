/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:48:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/03 22:24:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "object.h"
#include "bvh.h"
#include "render.h"

bool hit_box(t_ray *ray, t_aabb_bvh *bvh);

inline t_object	*get_nearest_2(t_ray *ray, t_aabb_bvh *bvh)
{
	t_object	*object[2];

	object[0] = bvh->object_a;
	object[1] = bvh->object_b;
	if (object[0]->f(ray, object[0], &object[0]->t) == 0)
	{
		if (object[1]->f(ray, object[1], &object[1]->t) == 0)
			return (NULL);
		return (object[1]);
	}
	if (object[1]->f(ray, object[1], &object[1]->t) == 0)
		return (object[0]);
	if (object[0]->t < object[1]->t)
		return (object[0]);
	return (object[1]);
}

t_object	*hit_triangle_bvh(t_ray *ray, t_aabb_bvh *bvh);

inline t_object	*hit_triangle_bvh(t_ray *ray, t_aabb_bvh *bvh)
{
	t_object	*object_a;
	t_object	*object_b;

	if (bvh->depth == 1)
		return (get_nearest_2(ray, bvh));
	if (bvh->depth == 0)
	{
		if (bvh->object_a->f(ray, bvh->object_a, &bvh->object_a->t) == 0)
			return (NULL);
		return (bvh->object_a);
	}
	object_a = hit_triangle_bvh(ray, bvh->next_a);
	if (!object_a)
		return (hit_triangle_bvh(ray, bvh->next_b));
	object_b = hit_triangle_bvh(ray, bvh->next_b);
	if (object_b != NULL)
	{
		if (object_a->t < object_b->t)
			return (object_a);
		return (object_b);
	}
	return (object_a);
}


static inline void bvh_check(float t1, float t2, float *t_min, float *t_max)
{
	*t_min = fmaxf(fminf(t1, t2), *t_min);
	*t_max = fminf(fmaxf(t1, t2), *t_max);
}

#include <float.h>
float	_hit_box(t_ray *ray, t_aabb_bvh *bvh)
{
	float	t_max;
	float	t_min;
	uint8_t	i;

	t_min = -FLT_MAX;
	t_max = FLT_MAX;
	i = 0;
	while (i < 3)
	{
		if (ray->dir.data[i] == .0f)
		{
			if (ray->pos.data[i] < bvh->min.data[i] ||
				ray->pos.data[i] > bvh->max.data[i])
			{
				return (FLT_MAX);
			}
		}
		else
		{
			bvh_check((bvh->min.data[i] - ray->pos.data[i]) / ray->dir.data[i],
				(bvh->max.data[i] - ray->pos.data[i]) / ray->dir.data[i],
				&t_min, &t_max);
			if (t_min > t_max)
				return (FLT_MAX);
		}
		i++;
	}
	return (t_min);
}


// define when the bvh will start iterate objects instead of box itself.
#define STOP_HIT_BVH 2

inline t_object *hit_aabb_bvh(t_ray *ray, t_aabb_bvh *bvh)
{
	t_object   *object_a;
	t_object   *object_b;

	if (bvh->depth < STOP_HIT_BVH)
		return (hit_triangle_bvh(ray, bvh));
	if (bvh->depth == 0)
	{
		if (bvh->object_a->f(ray, bvh->object_a, &bvh->object_a->t) == 0)
			return (NULL);
		return (bvh->object_a);
	}
	if (!hit_box(ray, bvh))
		return (NULL);
	object_a = hit_aabb_bvh(ray, bvh->next_a);
	if (!object_a)
		return (hit_aabb_bvh(ray, bvh->next_b));
	object_b = hit_aabb_bvh(ray, bvh->next_b);
	if (object_b != NULL)
	{
		if (object_a->t < object_b->t)
			return (object_a);
		return (object_b);
	}
	return (object_a);
}



// static inline void bvh_check(float t1, float t2, float *t_min, float *t_max)
// {
// 	*t_min = fmaxf(fminf(t1, t2), *t_min);
// 	*t_max = fminf(fmaxf(t1, t2), *t_max);
// }
//
// #include <float.h>
// float	_hit_box(t_ray *ray, t_aabb_bvh *bvh)
// {
// 	float	t_max;
// 	float	t_min;
// 	uint8_t	i;
//
// 	t_min = -FLT_MAX;
// 	t_max = FLT_MAX;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (ray->dir.data[i] == .0f)
// 		{
// 			if (ray->pos.data[i] < bvh->min.data[i] ||
// 				ray->pos.data[i] > bvh->max.data[i])
// 			{
// 				return (FLT_MAX);
// 			}
// 		}
// 		else
// 		{
// 			bvh_check((bvh->min.data[i] - ray->pos.data[i]) / ray->dir.data[i],
// 				(bvh->max.data[i] - ray->pos.data[i]) / ray->dir.data[i],
// 				&t_min, &t_max);
// 			if (t_min > t_max)
// 				return (FLT_MAX);
// 		}
// 		i++;
// 	}
// 	return (t_min);
// }
//
//
// // define when the bvh will start iterate objects instead of box itself.
// #define STOP_HIT_BVH 2
//
// inline t_object	*hit_aabb_bvh(t_ray *ray, t_aabb_bvh *bvh)
// {
// 	t_object	*object;
// 	float		distance_a;
// 	float		distance_b;
//
// 	if (bvh->depth < STOP_HIT_BVH)
// 		return (hit_triangle_bvh(ray, bvh));
// 	distance_a = _hit_box(ray, bvh->next_a);
// 	distance_b = _hit_box(ray, bvh->next_b);
//
// 	if (distance_a < distance_b)
// 	{
// 		object = hit_aabb_bvh(ray, bvh->next_a);
// 		if (!object)
// 		{
// 			if (distance_b != FLT_MAX)
// 				return (hit_aabb_bvh(ray, bvh->next_b));
// 			return (NULL);
// 		}
// 		return (object);
// 	}
// 	if (distance_b < distance_a)
// 	{
// 		object = hit_aabb_bvh(ray, bvh->next_b);
// 		if (!object)
// 		{
// 			if (distance_a != FLT_MAX)
// 				return (hit_aabb_bvh(ray, bvh->next_a));
// 			return (NULL);
// 		}
// 		return (object);
// 	}
// 	return (NULL);
// }
