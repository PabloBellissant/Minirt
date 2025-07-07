/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 07:02:08 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/24 07:02:09 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vec3.h"

int	hit_triangle(t_ray *ray, t_object *o, float *t);

inline int	hit_triangle(t_ray *ray, t_object *o, float *t)
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

	vec3_sub(&o->triangle.p1.pos, &o->triangle.p0.pos, &edge1);
	vec3_sub(&o->triangle.p2.pos, &o->triangle.p0.pos, &edge2);
	vec3_dot(&edge1, vec3_cross(&ray->dir, &edge2, &h), &a);
	if (a == 0.0f)
		return (0);
	f = 1.0f / a;
	vec3_sub(&ray->pos, &o->triangle.p0.pos, &s);
	u = f * *vec3_dot(&s, &h, &a);
	if (u < 0.0f || u > 1.0f)
		return (0);
	vec3_cross(&s, &edge1, &q);
	v = f * *vec3_dot(&ray->dir, &q, &a);
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	*t = f * *vec3_dot(&edge2, &q, &a);
	return (*t >= 0.0f);
}

// inline int	hit_triangle(t_ray *ray, t_triangle *triangle, float *t)
// {
// 	t_vec3	vertex0 = o->triangle.p0.pos;
// 	t_vec3	vertex1 = o->triangle.p1.pos;
// 	t_vec3	vertex2 = o->triangle.p2.pos;
// 	t_vec3	edge1;
// 	t_vec3	edge2;
// 	t_vec3	h;
// 	float	a;
// 	float	f;
// 	t_vec3	s;
// 	float	u;
// 	float	temp;
// 	t_vec3	q;
// 	float	v;
//
// 	vec3_sub(&vertex1, &vertex0, &edge1);
// 	vec3_sub(&vertex2, &vertex0, &edge2);
// 	vec3_cross(&ray->dir, &edge2, &h);
// 	vec3_dot(&edge1, &h, &a);
// 	if (a == 0.0f)
// 		return (0);
// 	f = 1.0f / a;
// 	vec3_sub(&ray->pos, &vertex0, &s);
// 	u = f * *vec3_dot(&s, &h, &temp);
// 	if (u < 0.0f || u > 1.0f)
// 		return (0);
// 	vec3_cross(&s, &edge1, &q);
// 	v = f * *vec3_dot(&ray->dir, &q, &temp);
// 	if (v < 0.0f || u + v > 1.0f)
// 		return (0);
// 	*t = f * *vec3_dot(&edge2, &q, &temp);
// 	return (*t >= 0.0f);
// }
