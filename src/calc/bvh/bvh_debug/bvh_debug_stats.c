/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_stats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:00:22 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:18:53 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static void	count_nodes_rec(t_bvh_header *h, size_t idx,
				size_t *leaf, size_t *internal)
{
	const t_bvh_node	*node;

	if (idx >= h->nodes.num_elements)
		return ;
	node = (t_bvh_node *)get_vector_value(&h->nodes, idx);
	if (node->children[0] <= 0)
		(*leaf)++;
	else
	{
		(*internal)++;
		count_nodes_rec(h, node->children[0], leaf, internal);
		count_nodes_rec(h, node->children[1], leaf, internal);
	}
}

static void	calc_depth_rec(t_bvh_header *h, size_t idx, int depth, size_t *sum)
{
	const t_bvh_node	*node;

	if (idx >= h->nodes.num_elements)
		return ;
	node = (t_bvh_node *)get_vector_value(&h->nodes, idx);
	if (node->children[0] <= 0)
		*sum += depth;
	else
	{
		calc_depth_rec(h, node->children[0], depth + 1, sum);
		calc_depth_rec(h, node->children[1], depth + 1, sum);
	}
}

static void	print_stats_line(size_t val, float pct, const char *label)
{
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM_HIGHLIGHT"%zu"
		C_RESET" "C_BRACKET"("C_PERCENT"%.2f%%"C_BRACKET")"C_RESET"\n",
		label, val, pct);
}

static void	init_stats_vars(size_t *leaf, size_t *internal, size_t *depth_sum)
{
	*leaf = 0;
	*internal = 0;
	*depth_sum = 0;
}

void	print_bvh_stats(t_bvh_header *h)
{
	size_t	leaf;
	size_t	internal;
	size_t	total;
	int		max_depth;
	size_t	depth_sum;

	init_stats_vars(&leaf, &internal, &depth_sum);
	max_depth = h->max_depth;
	count_nodes_rec(h, 0, &leaf, &internal);
	calc_depth_rec(h, 0, 0, &depth_sum);
	total = leaf + internal;
	printf(C_HEADER" ▎BVH Statistics                             "
		C_RESET"\n");
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM_HIGHLIGHT"%zu"
		C_RESET"\n", "Total nodes", total);
	print_stats_line(internal, 100.0f * (float)internal / (float)total,
		"Internal nodes");
	print_stats_line(leaf, 100.0f * (float)leaf / (float)total, "Leaf nodes");
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM"%d"C_RESET"\n",
		"Max depth", max_depth);
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM"%.2f"C_RESET"\n",
		"Avg leaf depth", (float)depth_sum / leaf);
	printf("\n");
}
