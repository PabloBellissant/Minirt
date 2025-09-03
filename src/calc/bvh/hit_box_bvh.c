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

static inline void	fill_hb(t_hit_box_bvh *hb, t_ray *ray,
	t_bvh *bvh, uint8_t i)
{
	hb->ray_origin = ray->pos.data[i];
	hb->ray_dir = ray->dir.data[i];
	hb->box_min = bvh->pos.data[i];
	hb->box_max = hb->box_min + bvh->size.data[i];
}

float	hit_box(t_ray *ray, t_bvh *bvh)
{
	t_hit_box_bvh	hb;
	uint8_t			i;

	hb.t_max = FLT_MAX;
	hb.t_min = -FLT_MAX;
	i = 0;
	while (i < 3)
	{
		fill_hb(&hb, ray, bvh, i);
		if (hb.ray_dir == .0f)
		{
			if ((hb.ray_origin < hb.box_min) || (hb.ray_origin > hb.box_max))
				return (-1);
		}
		else
		{
			bvh_check((hb.box_min - hb.ray_origin) / hb.ray_dir,
				(hb.box_max - hb.ray_origin) / hb.ray_dir,
				&hb.t_min, &hb.t_max);
			if (hb.t_min > hb.t_max)
				return (-1);
		}
		i++;
	}
	return (hb.t_max);
}
