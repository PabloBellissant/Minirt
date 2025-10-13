/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:58:06 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/02 01:58:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "minirt.h"

int hit_triangle(t_ray *ray, t_object *o, float *t)
{
	t_vec3	h;
	float	a;
	float	f;
	t_vec3	s;
	float	u;
	t_vec3	q;
	float	v;

	h = vec3_cross(ray->dir, o->triangle.edge_2);
	a = vec3_dot(o->triangle.edge_1, h);
	if (fabsf(a) < EPSILON)
		return (0);
	f = 1.0f / a;
	s = vec3_sub(ray->pos, o->triangle.p0.pos);
	u = f * vec3_dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return (0);
	q = vec3_cross(s, o->triangle.edge_1);
	v = f * vec3_dot(ray->dir, q);
	if (v < 0.0f || u + v > 1.0f)
		return 0;
	*t = f * vec3_dot(o->triangle.edge_2, q);
	return (*t > EPSILON);
}
