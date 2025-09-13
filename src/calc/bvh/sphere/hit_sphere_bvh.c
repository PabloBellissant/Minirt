/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_bvh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:26:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 05:26:50 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "bvh.h"
#include "render.h"

static inline int	_hit_sphere(t_ray *restrict ray, t_vec3 *pos, float radius_squared)
{
	t_vec3	oc;
	float	b;
	float	c;
	float	discriminant;
	float	t;

	oc = vec3_sub(ray->pos, *pos);
	b = vec3_dot(ray->dir, oc) * 2;
	c = vec3_dot(oc, oc) - radius_squared;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (0);
	c = sqrtf(discriminant);
	t = -b - c;
	if (t < 0)
		t = -b + c;
	t /= 2;
	return (t >= 0);
}

t_object	*hit_sphere_bvh(t_ray *ray, t_sphere_bvh *bvh)
{
	t_object	*object_a;
	t_object	*object_b;

	if (bvh->depth == 0)
	{
		if (bvh->object->f(ray, bvh->object, &bvh->object->t) == 0)
			return (NULL);
		return (bvh->object);
	}
	if (!_hit_sphere(ray, &bvh->pos, (bvh->size * bvh->size)))
		return (NULL);
	object_a = hit_sphere_bvh(ray, bvh->next_a);
	if (!object_a)
		return (hit_sphere_bvh(ray, bvh->next_b));
	object_b = hit_sphere_bvh(ray, bvh->next_b);
	if (object_b != NULL)
	{
		if (object_a->t < object_b->t)
			return (object_a);
		return (object_b);
	}
	return (object_a);
}
