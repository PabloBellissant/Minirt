/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:29:50 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 18:05:29 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "render.h"
#include "minirt.h"
#include "colors_types.h"

void		rasterize_sphere_bvh(t_sphere_bvh *bvh, t_params *p,
				int total_depth, t_data *data);
void		rasterize_aabb_bvh(int index, t_aabb_bvh *bvh_root,
				int total_depth, t_data *data);
t_rgb_int	float_to_rainbow(float f);

t_rgb_int	depth_to_rgb_int(int depth, int total_depth)
{
	float	t;

	t = (float)(depth) / (float)total_depth;
	return (float_to_rainbow(fmodf(t, 1.0f)));
}

void	full_render_aabb(int index, t_aabb_bvh *bvh,
	int total_depth, t_data *data)
{
	t_rgb_int	color;
	t_aabb_bvh	*node;
	int			i;
	int			child;

	if (!bvh || index < 0)
		return ;
	node = &bvh[index];
	color = depth_to_rgb_int(node->depth + data->params.bvh_color_offset,
			total_depth + 2);
	rasterize_cuboid(&node->cuboid, &data->mlx->img,
		&data->scene.camera, color);
	if (node->depth <= 1)
		return ;
	if (node->bvh_ary_type == BVH2)
	{
		full_render_aabb(index + 1, bvh, total_depth, data);
		if (node->next >= 0)
			full_render_aabb(node->next, bvh, total_depth, data);
	}
	else
	{
		i = 0;
		while (i < node->child_count)
		{
			child = node->children[i];
			if (child >= 0)
				full_render_aabb(child, bvh, total_depth, data);
			++i;
		}
	}
}


void	rasterize_bvh(void *bvh, t_params *p, int total_depth, t_data *data)
{
	if (!bvh)
		return ;
	if (data->scene.bvh.bvh_mode == 0)
		rasterize_sphere_bvh(bvh, p, total_depth, data);
	else if (data->scene.bvh.bvh_mode == 1)
		rasterize_aabb_bvh(0, bvh, total_depth, data);
}

void	rasterize_aabb_bvh(int index, t_aabb_bvh *bvh_root,
	int total_depth, t_data *data)
{
	t_rgb_int	color;
	t_aabb_bvh	*bvh;
	int			i;
	int			child;

	if (!bvh_root || index < 0)
		return ;
	if (data->params.bvh_depth == -1)
	{
		full_render_aabb(index, bvh_root, total_depth, data);
		return ;
	}
	bvh = &bvh_root[index];
	color = depth_to_rgb_int(bvh->depth + data->params.bvh_color_offset,
			total_depth - 1);
	if (bvh->depth > data->params.bvh_depth)
	{
		if (bvh->bvh_ary_type == BVH2)
		{
			printf("aled\n");
			rasterize_aabb_bvh(index + 1, bvh_root, total_depth, data);
			if (bvh->next >= 0)
				rasterize_aabb_bvh(bvh->next, bvh_root, total_depth, data);
		}
		else
		{
			i = 0;
			while (i < bvh->child_count)
			{
				child = bvh->children[i];
				if (child >= 0)
					rasterize_aabb_bvh(child, bvh_root, total_depth, data);
				++i;
			}
		}
	}
	else
	{
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img,
			&data->scene.camera, color);
	}
}
