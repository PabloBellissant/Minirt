/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:00:36 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:43:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

void	debug_bvh_tree(t_bvh_header *h)
{
	if (DEBUG)
	{
		print_bvh_debug_header();
		print_bvh_node_tree(h);
		print_bvh_config(h);
		print_bvh_stats(h);
	}
}
