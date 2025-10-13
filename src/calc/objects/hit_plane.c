/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:22:51 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/23 02:23:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "minirt.h"

int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t);

int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t)
{
	float	denom;

	denom = vec3_dot(ray->dir, o->plane.normal);
	if (fabsf(denom) < EPSILON)
		return (0);
	*t = vec3_dot(vec3_sub(o->plane.pos, ray->pos), o->plane.normal) / denom;
	return (*t >= EPSILON);
}
