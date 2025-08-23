/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:48:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/22 18:17:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <object.h>
#include "bvh.h"

float	hit_box(t_ray *ray, t_bvh *bvh);
//
// inline t_object	*hit_bvh(t_ray *ray, t_bvh *bvh)
// {
// 	t_object	*object_a;
// 	t_object	*object_b;
// 	float		a_temp;
// 	float		b_temp;
//
// 	while (bvh->depth != 0) // try with 1 after
// 	{
// 		a_temp = hit_box(ray, bvh->next_a);
// 		if (a_temp > 0)
// 		{
// 			b_temp = hit_box(ray, bvh->next_b);
// 			if (b_temp > 0)
// 			{
// 				if (a_temp < b_temp - fmaxf(bvh->next_b->size.x, fmaxf(bvh->next_b->size.y, bvh->next_b->size.z)) / 2)
// 				{
// 					object_a = hit_bvh(ray, bvh->next_a);
// 					if (!object_a)
// 						return (hit_bvh(ray, bvh->next_b));
// 					return (object_a);
// 				}
// 				if (b_temp < a_temp - fmaxf(bvh->next_a->size.x, fmaxf(bvh->next_a->size.y, bvh->next_a->size.z)) / 2)
// 				{
// 					object_b = hit_bvh(ray, bvh->next_b);
// 					if (!object_b)
// 						return (hit_bvh(ray, bvh->next_a));
// 					return (object_b);
// 				}
// 				object_a = hit_bvh(ray, bvh->next_a);
// 				if (!object_a)
// 					return (hit_bvh(ray, bvh->next_b));
// 				object_b = hit_bvh(ray, bvh->next_b);
// 				if (!object_b)
// 					return (object_a);
// 				if (object_a->t > object_b->t)
// 					return (object_b);
// 				return (object_a);
// 			}
// 			bvh = bvh->next_a;
// 		}
// 		else if (hit_box(ray, bvh->next_b) > 0)
// 			bvh = bvh->next_b;
// 		else
// 			return (NULL);
// 	}
// 	if (bvh->object->f(ray, bvh->object, &bvh->object->t) == 0)
// 		return (NULL);
// 	return (bvh->object);
// }

inline t_object	*hit_bvh(t_ray *ray, t_bvh *bvh)
{
	t_object	*object_a;
	t_object	*object_b;

	if (bvh->depth == 0)
	{
		if (bvh->object->f(ray, bvh->object, &bvh->object->t) == 0)
			return (NULL);
		return (bvh->object);
	}
	if (hit_box(ray, bvh) < 0)
		return (NULL);
	object_a = hit_bvh(ray, bvh->next_a);
	if (object_a == NULL)
		return (hit_bvh(ray, bvh->next_b));
	object_b = hit_bvh(ray, bvh->next_b);
	if (object_b != NULL)
	{
		if (object_a->t < object_b->t)
			return (object_a);
		return (object_b);
	}
	return (object_a);
}
