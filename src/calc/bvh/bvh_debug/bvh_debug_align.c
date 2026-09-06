/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_align.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:59:12 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/08 23:29:41 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

int	get_num_width(size_t num)
{
	int	width;

	width = 1;
	while (num >= 10)
	{
		width++;
		num /= 10;
	}
	return (width);
}

void	calc_align_info(const t_bvh_header *h, t_align_info *info)
{
	int	tree_prefix_width;

	info->max_depth = h->max_depth;
	info->max_idx_width = get_num_width(h->nodes.num_elements - 1);
	tree_prefix_width = (info->max_depth * 4) + 4;
	info->base_padding = tree_prefix_width + 8 + info->max_idx_width;
	info->info_col = info->base_padding + 8;
}
