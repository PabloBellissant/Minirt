/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:55:18 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/11 20:55:21 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_sphere(const t_sphere *s, t_vec3 *min, t_vec3 *max);
static void	update_triangle(const t_triangle *t, t_vec3 *min, t_vec3 *max);

void	get_min_max(t_object *o, t_vec3 *min, t_vec3 *max)
{
	if (o->type == TRIANGLE)
	{
		update_triangle(&o->triangle, min, max);
	}
	else
		update_sphere(&o->sphere, min, max);
}

static void	update_sphere(const t_sphere *s, t_vec3 *min, t_vec3 *max)
{
	float	radius;

	radius = s->diameter / 2.0f;
	min->x = s->pos.x - radius;
	min->y = s->pos.y - radius;
	min->z = s->pos.z - radius;
	max->x = min->x + s->diameter;
	max->y = min->y + s->diameter;
	max->z = min->z + s->diameter;
}

static void	update_triangle(const t_triangle *t, t_vec3 *min, t_vec3 *max)
{
	min->x = fminf(
			fminf(t->p0.pos.x, t->p1.pos.x), t->p2.pos.x);
	min->y = fminf(
			fminf(t->p0.pos.y, t->p1.pos.y), t->p2.pos.y);
	min->z = fminf(
			fminf(t->p0.pos.z, t->p1.pos.z), t->p2.pos.z);
	max->x = fmaxf(
			fmaxf(t->p0.pos.x, t->p1.pos.x), t->p2.pos.x);
	max->y = fmaxf(
			fmaxf(t->p0.pos.y, t->p1.pos.y), t->p2.pos.y);
	max->z = fmaxf(
			fmaxf(t->p0.pos.z, t->p1.pos.z), t->p2.pos.z);
}
