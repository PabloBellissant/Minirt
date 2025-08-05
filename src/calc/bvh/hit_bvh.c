/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:48:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:28 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "bvh.h"
#include "calc.h"

bool	hit_box(t_ray *ray, t_bvh *bvh);
void	get_t(t_ray *ray, t_object *object, float *t);

static inline void	check_hit(t_ray *ray, t_object **obj,
	float *obj_t, t_bvh *next)
{
	if (hit_box(ray, next) == true)
	{
		*obj = hit_bvh(ray, next);
		get_t(ray, *obj, obj_t);
	}
}

inline t_object	*hit_bvh(t_ray *ray, t_bvh *bvh)
{
	t_object	*object_a;
	t_object	*object_b;
	float		object_a_t;
	float		object_b_t;

	if (bvh->depth == 0)
	{
		get_t(ray, bvh->object, &object_a_t);
		if (isnan(object_a_t))
			return (NULL);
		return (bvh->object);
	}
	object_a_t = NAN;
	object_b_t = NAN;
	check_hit(ray, &object_a, &object_a_t, bvh->next_a);
	check_hit(ray, &object_b, &object_b_t, bvh->next_b);
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
		if (hit_plane(ray, object, t) == 0)
			*t = NAN;
		return ;
	}
	if (object->type == SPHERE)
	{
		if (hit_sphere(ray, object, t) == 0)
			*t = NAN;
		return ;
	}
	if (object->type == CYLINDER)
	{
		if (hit_cylinder(ray, object, t) == 0)
			*t = NAN;
		return ;
	}
	*t = NAN;
}
