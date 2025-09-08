/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:23:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/08 03:07:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

int	hit_sphere(t_ray *ray, t_object *o, float *t);

inline int	hit_sphere(t_ray *restrict ray, t_object *restrict o, float *t)
{
	t_vec3	oc;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_sub(ray->pos, o->sphere.pos);
	b = vec3_dot(ray->dir, oc) * 2;
	c = vec3_dot(oc, oc) - o->sphere.radius_squared;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (0);
	c = sqrtf(discriminant);
	*t = -b - c;
	if (*t < 0)
		*t = -b + c;
	*t /= 2;
	return (*t >= 0);
}
