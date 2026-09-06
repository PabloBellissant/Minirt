/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_bins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 07:27:02 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 12:23:51 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

void	sah_object_bounds(const t_bvh_shape bvh_shape,
			const t_bvh_bounds parent_bounds,
			const t_object *obj, t_bvh_bounds *out);

float	sah_best_split_cost(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds,
			const t_sah_bucket bins[SAH_NUM_BINS], t_sah_plan *plan);

size_t	get_sah_bin_idx(const t_bvh_bounds parent_bounds, const t_object obj,
			const t_sah_plan plan)
{
	const float	key = key_obj(plan.bvh_shape, parent_bounds, obj, plan.axis);
	size_t		bin_idx;

	bin_idx = (key - plan.cmin_proj.s[plan.axis]) * plan.inv_extent;
	if (bin_idx >= SAH_NUM_BINS)
		return (SAH_NUM_BINS - 1);
	return (bin_idx);
}

static inline void	sah_bins_fill(const t_bvh_bounds parent_bounds,
						const t_vector prim, const t_sah_plan plan,
						t_sah_bucket bins[SAH_NUM_BINS])
{
	size_t			i;
	t_object		*obj;
	size_t			bin_idx;
	t_bvh_bounds	ob;

	obj = (t_object *)prim.data;
	i = 0;
	while (i < prim.num_elements)
	{
		bin_idx = get_sah_bin_idx(parent_bounds, obj[i], plan);
		sah_object_bounds(plan.bvh_shape, parent_bounds, &obj[i], &ob);
		if (bins[bin_idx].count == 0)
			bins[bin_idx].bounds = ob;
		else
			bins[bin_idx].bounds = sah_merge_bounds(plan.bvh_shape,
					bins[bin_idx].bounds, ob);
		bins[bin_idx].count++;
		i++;
	}
}

void	sah_bins_best_split(const t_bvh_header *bvh_header,
				const t_bvh_bounds parent_bounds, const t_vector prim,
				t_sah_plan *plan)
{
	t_sah_bucket	bins[SAH_NUM_BINS];
	size_t			i;

	i = 0;
	while (i < SAH_NUM_BINS)
	{
		bins[i].count = 0;
		ft_bzero(&bins[i].bounds, sizeof(bins[i].bounds));
		i++;
	}
	plan->bvh_shape = bvh_header->shape;
	sah_bins_fill(parent_bounds, prim, *plan, bins);
	plan->cost = sah_best_split_cost(bvh_header, parent_bounds, bins, plan);
}
