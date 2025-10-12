/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_sphere_bvh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 06:43:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/11 06:43:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "colors_types.h"

t_rgb_int	depth_to_rgb_int(int depth, int total_depth);

void		full_render_sphere(t_sphere_bvh *bvh, int target_depth,
				int total_depth, t_data *data);

void	rasterize_sphere_bvh(t_sphere_bvh *bvh, t_params *p,
				int total_depth, t_data *data)
{
	t_rgb_int	rgb;
	t_rgb_int	color;
	t_sphere	sphere;

	rgb = depth_to_rgb_int(p->bvh_depth + data->params.bvh_color_offset,
			total_depth);
	color.r = rgb.r;
	color.g = rgb.g;
	color.b = rgb.b;
	if (p->bvh_depth == -1)
	{
		full_render_sphere(bvh, total_depth, total_depth, data);
		return ;
	}
	if (bvh->depth > p->bvh_depth && p->bvh_depth >= 0)
	{
		rasterize_sphere_bvh(bvh->next_a, p, total_depth, data);
		rasterize_sphere_bvh(bvh->next_b, p, total_depth, data);
	}
	else
	{
		sphere.diameter = bvh->size * 2;
		sphere.pos = bvh->pos;
		rasterize_sphere(&sphere, &data->mlx->img, &data->scene.camera, color);
	}
}

void	full_render_sphere(t_sphere_bvh *bvh, int target_depth,
	int total_depth, t_data *data)
{
	t_rgb_int	rgb;
	t_sphere	sphere;

	sphere.diameter = bvh->size * 2;
	sphere.pos = bvh->pos;
	rgb = depth_to_rgb_int(target_depth + data->params.bvh_color_offset,
			total_depth);
	rasterize_sphere(&sphere, &data->mlx->img, &data->scene.camera, rgb);
	if (bvh->depth > 0)
	{
		full_render_sphere(bvh->next_a, target_depth - 1, total_depth, data);
		full_render_sphere(bvh->next_b, target_depth - 1, total_depth, data);
	}
}
