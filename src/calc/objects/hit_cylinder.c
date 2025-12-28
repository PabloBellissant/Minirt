/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:23:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/08 02:27:13 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "render.h"
#include "calc.h"

static void	init_cylinder_quadratic(t_quadratic *q, t_cylinder *cyl, t_ray *r)
{
	const t_vec3	oc = vec3_sub(r->origin, cyl->pos);

	q->dd = vec3_dot(r->dir, cyl->rot);
	q->oo = vec3_dot(oc, cyl->rot);
	q->a = vec3_dot(r->dir, r->dir) - q->dd * q->dd;
	q->b = 2.0f * (vec3_dot(r->dir, oc) - q->dd * q->oo);
	q->c = vec3_dot(oc, oc) - q->oo * q->oo - cyl->radius * cyl->radius;
}

int	hit_cylinder(t_ray *ray, t_object *o, float *t_in)
{
	t_quadratic	q;
	float		y;

	init_cylinder_quadratic(&q, &o->cylinder, ray);
	if (!solve_quadratic(&q))
		return (0);
	*t_in = FLT_MAX;
	if (q.t_min > 0)
	{
		y = q.oo + q.t_min * q.dd;
		if (y >= 0.0f && y <= o->cylinder.height)
			*t_in = q.t_min;
	}
	if (q.t_max > 0)
	{
		y = q.oo + q.t_max * q.dd;
		if (y >= 0.0f && y <= o->cylinder.height && q.t_max < *t_in)
		{
			*t_in = q.t_max;
			return (1);
		}
	}
	return (*t_in >= FLT_MAX);
}

float	get_cylinder_t_out(t_ray *ray, t_object *o)
{
	t_quadratic	q;

	init_cylinder_quadratic(&q, &o->cylinder, ray);
	if (!solve_quadratic(&q))
		return (0);
	return (fmaxf(q.t_min, q.t_max));
}
