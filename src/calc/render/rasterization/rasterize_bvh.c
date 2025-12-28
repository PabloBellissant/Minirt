/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:29:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 00:53:51 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "colors_types.h"

void		rasterize_sphere_bvh(t_sphere_bvh *bvh, t_params *p,
				int total_depth, t_data *data);
void		rasterize_aabb_bvh(t_aabb_bvh *bvh, t_params *p,
				int total_depth, t_data *data);
t_rgb_int	float_to_rainbow(float f);

t_rgb_int	depth_to_rgb_int(int depth, int total_depth)
{
	float	t;

	t = (float)(depth) / (float)total_depth;
	return (float_to_rainbow(fmodf(t, 1.0f)));
}

void	full_render_aabb(t_aabb_bvh *bvh, int target_depth,
	int total_depth, t_data *data)
{
	t_rgb_int	rgb;

	rgb = depth_to_rgb_int(target_depth + data->params.bvh_color_offset,
			total_depth + 2);
	rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, rgb);
	if (bvh->depth > 0)
	{
		full_render_aabb(bvh->next_a, target_depth - 1, total_depth, data);
		full_render_aabb(bvh->next_b, target_depth - 1, total_depth, data);
	}
}

void	rasterize_bvh(void *bvh, t_params *p, int total_depth, t_data *data)
{
	if (!bvh)
		return ;
	if (data->scene.bvh.bvh_mode == 0)
		rasterize_sphere_bvh(bvh, p, total_depth, data);
	else if (data->scene.bvh.bvh_mode == 1)
		rasterize_aabb_bvh(bvh, p, total_depth, data);
}

void	rasterize_aabb_bvh(t_aabb_bvh *bvh, t_params *p,
	int total_depth, t_data *data)
{
	t_rgb_int	rgb;
	t_rgb_int	color;

	rgb = depth_to_rgb_int(p->bvh_depth + data->params.bvh_color_offset,
			total_depth - 1);
	color.r = rgb.r;
	color.g = rgb.g;
	color.b = rgb.b;
	if (p->bvh_depth == -1)
	{
		full_render_aabb(bvh, total_depth, total_depth, data);
		return ;
	}
	if (bvh->depth > p->bvh_depth)
	{
		rasterize_aabb_bvh(bvh->next_a, p, total_depth, data);
		rasterize_aabb_bvh(bvh->next_b, p, total_depth, data);
	}
	else
	{
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img,
			&data->scene.camera, color);
	}
}
