/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_box_bvh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:23:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 03:50:43 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "float.h"
#include "bvh.h"
#include "calc.h"

bool	hit_box(t_ray *ray, t_aabb_bvh *bvh)
{
	float	t_min;
	float	t_max;
	t_vec3	min;
	t_vec3	max;

	min = vec3_mult(vec3_sub(bvh->min, ray->origin), ray->inv_dir);
	max = vec3_mult(vec3_sub(bvh->max, ray->origin), ray->inv_dir);
	t_min = fminf(min.x, max.x);
	t_max = fmaxf(min.x, max.x);
	t_min = fmaxf(fminf(min.y, max.y), t_min);
	t_max = fminf(fmaxf(min.y, max.y), t_max);
	if (t_min > t_max)
		return (false);
	t_min = fmaxf(fminf(min.z, max.z), t_min);
	t_max = fminf(fmaxf(min.z, max.z), t_max);
	if (t_min > t_max)
		return (false);
	return (true);
}
