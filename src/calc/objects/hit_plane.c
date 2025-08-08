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

int	hit_plane(t_ray *ray, t_plane *p, float *t);

inline int	hit_plane(t_ray *restrict ray, t_plane *restrict p, float *t)
{
	float	norm;

	norm = (ray->dir.x * p->normal.x)
		+ (ray->dir.y * p->normal.y)
		+ (ray->dir.z * p->normal.z);
	if (norm == 0)
		return (0);
	*t = (((p->pos.x - ray->pos.x) * p->normal.x)
			+ ((p->pos.y - ray->pos.y) * p->normal.y)
			+ ((p->pos.z - ray->pos.z) * p->normal.z)) / norm;
	return (*t >= 0);
}
