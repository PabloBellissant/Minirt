/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:23:29 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 16:31:37 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "render.h"

#define BVH8_QUEUE_SIZE	32
#define BVH8_MAX_CHILDREN	8

static void	bvh8_init_node(t_aabb_bvh *node)
{
	int	i;

	node->min.x = FLT_MAX;
	node->min.y = FLT_MAX;
	node->min.z = FLT_MAX;
	node->max.x = -FLT_MAX;
	node->max.y = -FLT_MAX;
	node->max.z = -FLT_MAX;
	i = 0;
	while (i < 8)
	{
		node->children[i] = -1;
		++i;
	}
	node->child_count = 0;
	node->depth = 0;
	node->skip = -1;
	node->bvh_ary_type = BVH8;
}

static void	bvh8_expand_aabb(t_aabb_bvh *node, const t_aabb_bvh *child)
{
	if (child->min.x < node->min.x)
		node->min.x = child->min.x;
	if (child->min.y < node->min.y)
		node->min.y = child->min.y;
	if (child->min.z < node->min.z)
		node->min.z = child->min.z;
	if (child->max.x > node->max.x)
		node->max.x = child->max.x;
	if (child->max.y > node->max.y)
		node->max.y = child->max.y;
	if (child->max.z > node->max.z)
		node->max.z = child->max.z;
}

static int	bvh8_collapse_node(const t_aabb_bvh *bvh2, int bvh2_size,
							t_aabb_bvh *out, int *out_count,
							int bvh2_index)
{
	t_aabb_bvh	node;
	int			queue[BVH8_QUEUE_SIZE];
	int			q_head;
	int			q_tail;
	int			child_idx;
	int			j;
	const t_aabb_bvh	*current;
	int			node_index;

	bvh8_init_node(&node);
	q_head = 0;
	q_tail = 0;
	if (bvh2_index < 0 || bvh2_index >= bvh2_size)
		return (-1);
	if (bvh2[bvh2_index].depth == 0)
	{
		node.min = bvh2[bvh2_index].min;
		node.max = bvh2[bvh2_index].max;
		node.children[0] = -1 - bvh2[bvh2_index].object;
		node.child_count = 1;
		node.depth = 0;
		node_index = *out_count;
		out[*out_count] = node;
		(*out_count)++;
		return (node_index);
	}
	queue[q_tail++] = bvh2_index + 1;
	queue[q_tail++] = bvh2[bvh2_index].next;
	child_idx = 0;
	while (q_head < q_tail && child_idx < BVH8_MAX_CHILDREN)
	{
		j = queue[q_head++];
		if (j < 0 || j >= bvh2_size)
			continue ;
		current = &bvh2[j];
		if (node.child_count == 0)
			node.min = current->min;
		else
			bvh8_expand_aabb(&node, current);
		if (current->max.x > node.max.x)
			node.max.x = current->max.x;
		if (current->max.y > node.max.y)
			node.max.y = current->max.y;
		if (current->max.z > node.max.z)
			node.max.z = current->max.z;
		if (current->depth == 0)
			node.children[child_idx] = -1 - current->object;
		else
		{
			node.children[child_idx] = bvh8_collapse_node(bvh2, bvh2_size,
				out, out_count, j);
			if (node.children[child_idx] < 0)
				return (-1);
		}
		node.child_count++;
		child_idx++;
	}
	node.depth = 1;
	node_index = *out_count;
	out[*out_count] = node;
	(*out_count)++;
	return (node_index);
}

int	create_bvh8_from_bvh2(const t_aabb_bvh *bvh2, int bvh2_size,
						t_aabb_bvh *out_bvh8, int out_capacity,
						int *out_size)
{
	int	node_count;

	if (!bvh2 || bvh2_size <= 0 || !out_bvh8 || out_capacity <= 0)
	{
		if (out_size)
			*out_size = 0;
		return (0);
	}
	node_count = 0;
	if (bvh8_collapse_node(bvh2, bvh2_size, out_bvh8,
			&node_count, 0) < 0)
		return (-1);
	if (node_count > out_capacity)
		return (-1);
	if (out_size)
		*out_size = node_count;
	return (0);
}

