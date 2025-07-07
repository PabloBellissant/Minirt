/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 06:55:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/27 06:55:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"

int	hit_cylinder(t_ray *ray, t_object *o, float *t);

inline int	hit_cylinder(t_ray *ray, t_object *o, float *t)
{
	float	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	float	b = 2 * (ray->dir.x * (ray->pos.x - o->cylinder.pos.x) + ray->dir.z * (ray->pos.z - o->cylinder.pos.z));
	float	c = (ray->pos.x - o->cylinder.pos.x) * (ray->pos.x - o->cylinder.pos.x) + (ray->pos.z - o->cylinder.pos.z) * (ray->pos.z - o->cylinder.pos.z) - o->cylinder.diameter;
	float	delta = b * b - 4 * (a*c);

	if (delta == 0)
		return (0);
	float	t1 = (-b - sqrtf(delta)) / (2 * a);
	float	t2 = (-b + sqrtf(delta)) / (2 * a);

	if (t1 > t2)
		*t = t2;
	else
		*t = t1;
	float	r = ray->pos.y + *t * ray->dir.y;
	if (r >= o->cylinder.pos.y && r <= o->cylinder.pos.y + o->cylinder.height)
		return (1);
	return (0);
}
