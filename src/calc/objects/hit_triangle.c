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

#include "minirt.h"

int	hit_triangle(t_ray *ray, t_object *o, float *t);

int	hit_triangle(t_ray *ray, t_object *o, float *t)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	float	a;
	float	f;
	float	u;
	float	v;

	edge1 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
	edge2 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
	h = vec3_cross(ray->dir, edge2);
	a = vec3_dot(edge1, h);
	if (a == 0.0f)
		return (0);
	f = 1.0f / a;
	s = vec3_sub(ray->pos, o->triangle.p0.pos);
	u = f * vec3_dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return (0);
	q = vec3_cross(s, edge1);
	v = f * vec3_dot(ray->dir, q);
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	*t = f * vec3_dot(edge2, q);
	return (*t >= 0);
}
