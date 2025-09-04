/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:35:36 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/04 00:35:38 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"

void	rasterize_bvh(t_bvh *bvh, int depth, int total_depth, t_data *data)
{
	int	color;

	color = depth / total_depth * 16000;
	if (bvh->depth > depth)
	{
		rasterize_bvh(bvh->next_a, depth, total_depth, data);
		rasterize_bvh(bvh->next_b, depth, total_depth, data);
	}
	else if (bvh->depth >= 0)
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, 0xFF00FF);
}
