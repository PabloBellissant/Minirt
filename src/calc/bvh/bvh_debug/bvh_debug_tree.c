/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:59:43 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:52:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static inline void	copy_prefix(const char *pfx, char *new_pfx, const bool last)
{
	size_t	len;

	len = ft_strlcpy(new_pfx, pfx, MAX_PRINT_SIZE);
	if (last)
		ft_strlcpy(new_pfx + len, "    ", 5);
	else
		ft_strlcpy(new_pfx + len, "\xE2\x94\x82   ", 7);
}

static inline void	debug_node_rec(size_t idx, const char *pfx,
				t_align_info a, const bool last)
{
	const t_bvh_node	*node;
	char				new_pfx[MAX_PRINT_SIZE];

	if (idx >= a.h->nodes.num_elements)
		return ;
	node = (t_bvh_node *)get_vector_value(&a.h->nodes, idx);
	if (last)
		printf(C_TREE"%s└── "C_RESET, pfx);
	else
		printf(C_TREE"%s├── "C_RESET, pfx);
	if (node->children[0] <= 0)
		print_leaf_info(node->object_id, idx, a, pfx);
	else
		print_node_info(node, idx, a, pfx);
	print_bounds(&node->bounds, a.h->shape);
	printf("\n");
	if (node->children[0] > 0)
	{
		copy_prefix(pfx, new_pfx, last);
		a.cur_depth++;
		debug_node_rec(node->children[0], new_pfx, a, false);
		debug_node_rec(node->children[1], new_pfx, a, true);
	}
}

void	print_bvh_node_tree(t_bvh_header *h)
{
	t_align_info	align;

	if (h->nodes.num_elements == 0)
	{
		printf(C_DIM"  (empty tree)"C_RESET"\n\n");
		return ;
	}
	calc_align_info(h, &align);
	align.cur_depth = 0;
	align.h = h;
	printf(C_HEADER" ▎BVH Tree Structure                         "
		C_RESET"\n\n");
	debug_node_rec(0, "", align, true);
	printf("\n");
}
