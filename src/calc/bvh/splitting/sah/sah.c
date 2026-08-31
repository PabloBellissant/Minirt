/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 07:19:12 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:30:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int		sah_choose_plan(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector prim,
			t_sah_plan *out);

size_t	get_sah_bin_idx(const t_bvh_bounds parent_bounds,
			const t_object obj, const t_sah_plan plan);

static inline int	sah_partition(const t_bvh_bounds parent_bounds,
	const t_vector prim, const t_sah_plan plan, t_vector child[BVH_LR])
{
	size_t		i;
	t_object	*obj;
	size_t		bin_idx;

	vector_init(&child[BVH_L], sizeof(t_object));
	vector_init(&child[BVH_R], sizeof(t_object));
	obj = (t_object *)prim.data;
	i = 0;
	while (i < prim.num_elements)
	{
		bin_idx = get_sah_bin_idx(parent_bounds, obj[i], plan);
		if ((ssize_t)bin_idx <= plan.split_bin)
		{
			if (vector_add(&child[BVH_L], &obj[i], 1) != 0)
				return (-1);
		}
		else
		{
			if (vector_add(&child[BVH_R], &obj[i], 1) != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	sah(const t_bvh_header *bvh_header, const t_bvh_bounds parent_bounds,
			const t_vector prim, t_vector child_prim[BVH_LR])
{
	t_sah_plan	plan;

	plan.bvh_shape = bvh_header->shape;
	if (!sah_choose_plan(bvh_header, parent_bounds, prim, &plan))
		return (med_prim(bvh_header, parent_bounds, prim, child_prim));
	if (sah_partition(parent_bounds, prim, plan, child_prim) != 0)
		return (-1);
	if ((child_prim[BVH_L].num_elements == 0)
		|| (child_prim[BVH_R].num_elements == 0))
	{
		free_vector(&child_prim[BVH_L]);
		free_vector(&child_prim[BVH_R]);
		return (med_prim(bvh_header, parent_bounds, prim, child_prim));
	}
	return (0);
}
