/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:38:37 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:11:18 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	hit_plane(t_ray *ray, t_object *o, float *t);

inline int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t)
{
	float	norm;

	norm = (ray->dir.x * o->plane.normal.x)
		+ (ray->dir.y * o->plane.normal.y)
		+ (ray->dir.z * o->plane.normal.z);
	if (norm == 0)
		return (0);
	*t = (((o->plane.pos.x - ray->pos.x) * o->plane.normal.x)
			+ ((o->plane.pos.y - ray->pos.y) * o->plane.normal.y)
			+ ((o->plane.pos.z - ray->pos.z) * o->plane.normal.z)) / norm;
	return (*t >= 0);
}
