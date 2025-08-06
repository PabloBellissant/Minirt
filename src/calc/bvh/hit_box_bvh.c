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

#include "bvh.h"
#include "calc.h"

static inline void	swap_float(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static inline void	bvh_check(float t1, float t2, float *t_min, float *t_max)
{
	if (t1 > t2)
		swap_float(&t1, &t2);
	if (t1 > *t_min)
		*t_min = t1;
	if (t2 < *t_max)
		*t_max = t2;
}

static inline void	fill_hb(t_hit_box_bvh *hb, t_ray *ray,
	t_bvh *bvh, uint8_t i)
{
	hb->ray_origin = ((float *)&ray->pos)[i];
	hb->ray_dir = ((float *)&ray->dir)[i];
	hb->box_min = ((float *)&bvh->pos)[i];
	hb->box_max = hb->box_min + ((float *)&bvh->size)[i];
}

bool	hit_box(t_ray *ray, t_bvh *bvh)
{
	t_hit_box_bvh	hb;
	uint8_t			i;

	hb.t_max = INFINITY;
	hb.t_min = -INFINITY;
	i = 0;
	while (i < 3)
	{
		fill_hb(&hb, ray, bvh, i);
		if (fabsf(hb.ray_dir) < 1e-8f)
		{
			if ((hb.ray_origin < hb.box_min) || (hb.ray_origin > hb.box_max))
				return (false);
		}
		else
		{
			bvh_check((hb.box_min - hb.ray_origin) / hb.ray_dir,
				(hb.box_max - hb.ray_origin) / hb.ray_dir,
				&hb.t_min, &hb.t_max);
			if (hb.t_min > hb.t_max)
				return (false);
		}
		i++;
	}
	return (hb.t_max >= 0);
}
