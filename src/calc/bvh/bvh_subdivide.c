/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_subdivide.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:48:21 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 03:45:05 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int		free_bvh_build_pack(t_bvh_build_pack childs[BVH_LR]);

static inline int	bvh_emit_node(t_bvh_header *bvh_header,
						t_bvh_bounds cur_bounds, size_t *cur_idx)
{
	t_bvh_node		temp_node;

	ft_bzero(&temp_node, sizeof(temp_node));
	temp_node.bounds = cur_bounds;
	*cur_idx = bvh_header->nodes.num_elements;
	if (vector_add(&bvh_header->nodes, &temp_node, 1) != 0)
		return (-1);
	return (0);
}

/*
	Return 0 if not a leaf and 1 if is a leaf
*/
static inline int	bvh_try_leaf(t_bvh_header *bvh_header,
						t_vector primitives, size_t cur_idx)
{
	if (primitives.num_elements <= 1)
	{
		if (primitives.num_elements == 1)
			((t_bvh_node *)get_vector_value(&bvh_header->nodes,
				cur_idx))->object_id
				= ((t_object *)get_vector_value(&primitives, 0))->object_id;
		return (1);
	}
	return (0);
}

static inline int	bvh_split_and_evaluate_bounds(t_bvh_header *bvh_header,
						t_bvh_bounds cur_bounds, t_vector primitives,
						t_bvh_build_pack childs[BVH_LR])
{
	if (evaluate_split(bvh_header, cur_bounds, primitives, childs) != 0)
		return (-1);
	if ((childs[BVH_L].primitives.num_elements == 0)
		|| (childs[BVH_R].primitives.num_elements == 0))
	{
		free_vector(&childs[BVH_L].primitives);
		free_vector(&childs[BVH_R].primitives);
		return (1);
	}
	evaluate_bounds(bvh_header->shape, &childs[BVH_L]);
	evaluate_bounds(bvh_header->shape, &childs[BVH_R]);
	return (0);
}

ssize_t	bvh_subdivide(t_bvh_header *bvh_header, t_vector primitives,
			t_bvh_bounds cur_bounds);

static inline ssize_t	bvh_build_child(t_bvh_header *bvh_header,
							size_t cur_idx, int side, t_bvh_build_pack child)
{
	((t_bvh_node *)get_vector_value(&bvh_header->nodes,
		cur_idx))->children[side] = (int)bvh_header->nodes.num_elements;
	return (bvh_subdivide(bvh_header, child.primitives, child.bounds));
}

ssize_t	bvh_subdivide(t_bvh_header *bvh_header, t_vector primitives,
			t_bvh_bounds cur_bounds)
{
	size_t				cur_idx;
	t_bvh_build_pack	childs[BVH_LR];
	ssize_t				ret[BVH_LR];
	int					status;

	ft_bzero(childs, sizeof(childs));
	if (bvh_emit_node(bvh_header, cur_bounds, &cur_idx) != 0)
		return (-1);
	status = bvh_try_leaf(bvh_header, primitives, cur_idx);
	if (status == 1)
		return (0);
	status = bvh_split_and_evaluate_bounds(bvh_header, cur_bounds,
			primitives, childs);
	if ((status == -1) || (status == 1))
		return ((int)(status == -1) *-1);
	ret[BVH_L] = bvh_build_child(bvh_header, cur_idx, BVH_L, childs[BVH_L]);
	if (ret[BVH_L] == -1)
		return (free_bvh_build_pack(childs));
	ret[BVH_R] = bvh_build_child(bvh_header, cur_idx, BVH_R, childs[BVH_R]);
	free_bvh_build_pack(childs);
	if (ret[BVH_R] == -1)
		return (-1);
	return (max(ret[BVH_L], ret[BVH_R]) + 1);
}
