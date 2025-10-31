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
#include "calc.h"

static void	init_sphere_quadratic(t_quadratic *q, t_sphere *sp, t_ray *ray)
{
	const t_vec3	oc = vec3_sub(ray->pos, sp->pos);

	q->a = vec3_dot(ray->dir, ray->dir);
	q->b = 2.0f * vec3_dot(ray->dir, oc);
	q->c = vec3_dot(oc, oc) - sp->radius_squared;
}

int	hit_sphere(t_ray *ray, t_object *o, float *t_in)
{
	t_quadratic	q;

	init_sphere_quadratic(&q, &o->sphere, ray);
	if (!solve_quadratic(&q))
		return (0);
	*t_in = fminf(q.t_min, q.t_max);
	if (*t_in <= 0)
		*t_in = fmaxf(q.t_min, q.t_max);
	return (*t_in > EPSILON);
}

float	get_sphere_t_out(t_ray *ray, t_object *o)
{
	t_quadratic	q;
	float		t_out;

	init_sphere_quadratic(&q, &o->sphere, ray);
	if (!solve_quadratic(&q))
		return (0);
	t_out = fmaxf(q.t_min, q.t_max);
	return (t_out);
}
