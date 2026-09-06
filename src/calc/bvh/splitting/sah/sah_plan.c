/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 07:27:22 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:32:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int	sah_bins_best_split(const t_bvh_header *bvh_header,
		const t_bvh_bounds parent_bounds, const t_vector prim,
		t_sah_plan *plan);

static inline void	sah_centroid_bounds(const t_bvh_header *bvh_header,
		t_bvh_bounds parent_bounds, const t_vector prim, t_vec3 cmm[BVH_LR])
{
	size_t		i;
	t_object	*objects;
	t_axis		axis;
	float		p;

	cmm[BVH_L] = vec3_pinf();
	cmm[BVH_R] = vec3_ninf();
	objects = (t_object *)prim.data;
	i = 0;
	while (i < prim.num_elements)
	{
		axis = X_AXIS;
		while (axis < NUM_AXIS)
		{
			p = key_obj(bvh_header->shape, parent_bounds, objects[i], axis);
			cmm[BVH_L].s[axis] = fminf(cmm[BVH_L].s[axis], p);
			cmm[BVH_R].s[axis] = fmaxf(cmm[BVH_R].s[axis], p);
			axis++;
		}
		i++;
	}
}

static inline float	sah_inv_extent(t_vec3 cmm[BVH_LR], t_axis axis)
{
	const float	extent = cmm[BVH_R].s[axis] - cmm[BVH_L].s[axis];

	if (extent <= 0.f)
		return (0.f);
	return ((float)SAH_NUM_BINS / extent);
}

int	sah_choose_plan(const t_bvh_header *bvh_header,
		const t_bvh_bounds parent_bounds, const t_vector prim, t_sah_plan *out)
{
	t_sah_plan	plan[BVH_LR];
	t_vec3		cmm[BVH_LR];
	float		inv;
	t_axis		axis;

	sah_centroid_bounds(bvh_header, parent_bounds, prim, cmm);
	plan[BVH_L] = (t_sah_plan){.axis = X_AXIS, .split_bin = -1,
		.cmin_proj = cmm[BVH_L], .inv_extent = 0.f, .cost = SAH_SM};
	axis = X_AXIS;
	while (axis < NUM_AXIS)
	{
		inv = sah_inv_extent(cmm, axis);
		plan[BVH_R] = (t_sah_plan){.axis = axis, .split_bin = -1,
			.cmin_proj = cmm[BVH_L], .inv_extent = inv, .cost = SAH_SM};
		if (inv > 0.f)
			sah_bins_best_split(bvh_header, parent_bounds, prim, &plan[BVH_R]);
		if ((plan[BVH_R].split_bin != -1)
			&& (plan[BVH_R].cost < plan[BVH_L].cost))
			plan[BVH_L] = plan[BVH_R];
		axis++;
	}
	*out = plan[BVH_L];
	return (out->split_bin != -1);
}
