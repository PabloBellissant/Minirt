/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_light_bvh.c                                    :+:      :+:    :+:   */
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

// define when the bvh will start iterate objects instead of box itself.
#define STOP_HIT_BVH 2

bool		hit_box(t_ray *ray, t_aabb_bvh *bvh);

t_object	*hit_light_object(t_ray *ray, t_aabb_bvh *bvh);

inline t_object	*hit_light_bvh(t_ray *ray, t_aabb_bvh *bvh)
{
	t_object	*object;

	if (bvh->depth < STOP_HIT_BVH)
		return (hit_light_object(ray, bvh));
	if (!hit_box(ray, bvh))
		return (NULL);
	object = hit_aabb_bvh(ray, bvh->next_a);
	if (!object)
		return (hit_aabb_bvh(ray, bvh->next_b));
	return (object);
}

static inline t_object	*get_nearest_2(t_ray *ray, t_aabb_bvh *bvh)
{
	if (bvh->object_a->f(ray, bvh->object_a, &bvh->object_a->t) != 0)
		return (bvh->object_a);
	if (bvh->object_b->f(ray, bvh->object_b, &bvh->object_b->t) != 0)
		return (bvh->object_b);
	return (NULL);
}

t_object	*hit_light_object(t_ray *ray, t_aabb_bvh *bvh)
{
	t_object	*object;

	if (bvh->depth == 1)
		return (get_nearest_2(ray, bvh));
	if (bvh->depth == 0)
	{
		if (bvh->object_a
			&& bvh->object_a->f(ray, bvh->object_a, &bvh->object_a->t) == 0)
		{
			return (NULL);
		}
		return (bvh->object_a);
	}
	object = hit_light_object(ray, bvh->next_a);
	if (!object)
		return (hit_light_object(ray, bvh->next_b));
	return (object);
}
