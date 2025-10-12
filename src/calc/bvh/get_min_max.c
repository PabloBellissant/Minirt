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
static void	update_cylinder(const t_cylinder *c, t_vec3 *min, t_vec3 *max);

void	get_min_max(t_object *o, t_vec3 *min, t_vec3 *max)
{
	if (o->type == TRIANGLE)
	{
		update_triangle(&o->triangle, min, max);
	}
	else if (o->type == SPHERE)
	{
		update_sphere(&o->sphere, min, max);
	}
	else if (o->type == CYLINDER)
	{
		update_cylinder(&o->cylinder, min, max);
	}
}

static void	update_sphere(const t_sphere *s, t_vec3 *min, t_vec3 *max)
{
	min->x = s->pos.x - (s->diameter / 2);
	min->y = s->pos.y - (s->diameter / 2);
	min->z = s->pos.z - (s->diameter / 2);
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

static void	update_cylinder(const t_cylinder *c, t_vec3 *min, t_vec3 *max)
{
	t_vec3	temp;
	t_vec3	p2;

	p2 = vec3_add(c->pos, vec3_scale(c->rot, c->height));
	temp.x = c->radius * sqrtf(1.0f - c->rot.x * c->rot.x);
	temp.y = c->radius * sqrtf(1.0f - c->rot.y * c->rot.y);
	temp.z = c->radius * sqrtf(1.0f - c->rot.z * c->rot.z);
	min->x = fminf(c->pos.x - temp.x, p2.x - temp.x);
	max->x = fmaxf(c->pos.x + temp.x, p2.x + temp.x);
	min->y = fminf(c->pos.y - temp.y, p2.y - temp.y);
	max->y = fmaxf(c->pos.y + temp.y, p2.y + temp.y);
	min->z = fminf(c->pos.z - temp.z, p2.z - temp.z);
	max->z = fmaxf(c->pos.z + temp.z, p2.z + temp.z);
}
