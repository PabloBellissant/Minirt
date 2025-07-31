/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 06:55:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:50:13 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"

int	hit_cylinder(t_ray *ray, t_object *o, float *t);

float	*solve_quadtratic_equation(const float a, const float b, const float c,
		float *x)
{
	const float	delta = (b * b) - (4 * a * c);
	float		x1;
	float		x2;

	if (delta == 0)
		return (0);
	x1 = (-b - sqrtf(delta)) / (2 * a);
	x2 = (-b + sqrtf(delta)) / (2 * a);
	if (x1 > x2)
		*x = x2;
	else
		*x = x1;
	return (x);
}

inline int	hit_cylinder(t_ray *ray, t_object *o, float *t)
{
	const float	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	const float	b = 2 * (ray->dir.x * (ray->pos.x - o->cylinder.pos.x)
			+ ray->dir.z * (ray->pos.z - o->cylinder.pos.z));
	const float	c = ((ray->pos.x - o->cylinder.pos.x)
			* (ray->pos.x - o->cylinder.pos.x))
		+ ((ray->pos.z - o->cylinder.pos.z) * (ray->pos.z - o->cylinder.pos.z))
		- o->cylinder.diameter;
	float		r;

	solve_quadtratic_equation(a, b, c, t);
	r = ray->pos.y + *t * ray->dir.y;
	if (r >= o->cylinder.pos.y && r <= o->cylinder.pos.y + o->cylinder.height)
		return (1);
	return (0);
}
