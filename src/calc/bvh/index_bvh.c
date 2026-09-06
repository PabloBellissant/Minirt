/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 01:29:13 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/06 01:41:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "libft.h"

void	index_recur(t_bvh_node *bvh, int idx)
{
	if (bvh[idx].children[0] <= 0)
		return ;
	if (bvh[idx].children[1] > 0)
		bvh[idx + 1].skip = bvh[idx].children[1];
	else
		bvh[idx + 1].skip = bvh[idx].skip;
	index_recur(bvh, idx + 1);
	if (bvh[idx].children[1] > 0)
	{
		bvh[bvh[idx].children[1]].skip = bvh[idx].skip;
		index_recur(bvh, bvh[idx].children[1]);
	}
}

void	index_bvh(t_bvh_header bvh_header)
{
	t_bvh_node	*node;

	node = bvh_header.nodes.data;
	node[0].skip = -1;
	index_recur(bvh_header.nodes.data, 0);
}
