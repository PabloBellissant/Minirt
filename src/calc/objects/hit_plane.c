/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:38:37 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/23 03:38:38 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	hit_plane(t_ray *ray, t_object *o, float *t);

inline int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t)
{
	float	norm;

	norm = ray->dir.x * o->plane.normal.x + ray->dir.y * o->plane.normal.y + ray->dir.z * o->plane.normal.z;
	if (norm == 0)
		return (0);
	*t = ((o->plane.pos.x - ray->pos.x) * o->plane.normal.x + (o->plane.pos.y - ray->pos.y) * o->plane.normal.y + (o->plane.pos.z - ray->pos.z) * o->plane.normal.z) / norm;
	return (*t >= 0);
}
//
// inline int	hit_plane(t_ray *ray, t_plane *p, float *t)
// {
// 	t_vec3	dir;
// 	float	norm;
//
// 	dir = ray->dir;
// 	norm = dir.x * p->normal.x + dir.y * p->normal.y + dir.z * p->normal.z;
// 	if (norm == 0.0)
// 		return (0);
// 	dir.x = (p->pos.x - ray->pos.x);
// 	dir.y = (p->pos.y - ray->pos.y);
// 	dir.z = (p->pos.z - ray->pos.z);
// 	*t = (dir.x * p->normal.x + dir.y * p->normal.y + dir.z * p->normal.z) / norm;
// 	if (*t >= 0)
// 		return (1);
// 	return (0);
// }

// 207670