/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:38:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/07 02:43:28 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"

int	hit_sphere(t_ray *ray, t_object *o, float *t);

inline int	hit_sphere(t_ray *restrict ray, t_object *restrict o, float *t)
{
	t_vec4	oc;

	oc.x = ray->pos.x - o->sphere.pos.x;
	oc.y = ray->pos.y - o->sphere.pos.y;
	oc.z = ray->pos.z - o->sphere.pos.z;
	oc.w = ray->dir.x * oc.x;
	oc.w += ray->dir.y * oc.y;
	oc.w += ray->dir.z * oc.z;
	oc.w *= 2;
	oc.x = oc.x * oc.x;
	oc.x += oc.y * oc.y;
	oc.x += oc.z * oc.z;
	oc.x -= o->sphere.radius_squared;
	oc.y = oc.w * oc.w - 4 * oc.x;
	if (oc.y < 0)
		return (0);
	oc.x = sqrtf(oc.y);
	*t = -oc.w - oc.x;
	if (*t < 0)
		*t = -oc.w + oc.x;
	*t /= 2;
	return (*t >= 0);
}
