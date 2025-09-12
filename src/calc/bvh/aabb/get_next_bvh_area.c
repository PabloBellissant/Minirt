/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_bvh_area.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:15:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:17 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <math.h>

float	get_next_bvh_area(t_aabb_bvh *a, t_aabb_bvh *b)
{
	float	area;
	float	size;

	size = fmaxf(a->max.x, b->max.x) - fminf(a->min.x, b->min.x);
	area = size * size;
	size = fmaxf(a->max.y, b->max.y) - fminf(a->min.y, b->min.y);
	area += size * size;
	size = fmaxf(a->max.z, b->max.z) - fminf(a->min.z, b->min.z);
	area += size * size;
	return (area);
}
