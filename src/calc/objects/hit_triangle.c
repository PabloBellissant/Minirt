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

#define TRIANGLE_EPSILON 1e-6f

/*
	MollerTrumbore algorithm.
*/
int	hit_triangle(t_ray *ray, t_object *o, float *t)
{
	t_vec3	h;
	float	f;
	t_vec3	s;
	float	u;
	float	v;

	h = vec3_cross(ray->dir, o->triangle.edge_p2p0);
	f = vec3_dot(o->triangle.edge_p1p0, h);
	if (fabsf(f) < TRIANGLE_EPSILON)
		return (0);
	f = 1.0f / f;
	s = vec3_sub(ray->origin, o->triangle.p0.pos);
	u = f * vec3_dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return (0);
	s = vec3_cross(s, o->triangle.edge_p1p0);
	v = f * vec3_dot(ray->dir, s);
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	*t = f * vec3_dot(o->triangle.edge_p2p0, s);
	return (*t > TRIANGLE_EPSILON);
}
