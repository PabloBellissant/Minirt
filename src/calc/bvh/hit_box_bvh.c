/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_box_bvh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:23:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 03:50:43 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>
#include "bvh.h"
#include "calc.h"

static inline void bvh_check(float t1, float t2, float *t_min, float *t_max)
{
	*t_min = fmaxf(fminf(t1, t2), *t_min);
	*t_max = fminf(fmaxf(t1, t2), *t_max);
}

bool	hit_box(t_ray *ray, t_bvh *bvh)
{
	float	t_max;
	float	t_min;
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		if (ray->dir.data[i] == .0f)
		{
			if (ray->pos.data[i] < bvh->min.data[i] ||
				ray->pos.data[i] > bvh->max.data[i])
			{
				return (false);
			}
		}
		else
		{
			bvh_check((bvh->min.data[i] - ray->pos.data[i]) / ray->dir.data[i],
				(bvh->max.data[i] - ray->pos.data[i]) / ray->dir.data[i],
				&t_min, &t_max);
			if (t_min > t_max)
				return (false);
		}
		i++;
	}
	return (true);
}
