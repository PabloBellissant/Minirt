/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:29:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/05 01:30:51 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "colors_types.h"

static inline t_rgb_int	rgb_to_rgb_int(float r, float g, float b)
{
	return ((t_rgb_int) {{r * 255.0f, g * 255.0f, b * 255.0f}});
}

t_rgb_int float_to_rainbow(float f)
{
	float		zone;
	float		x;

	f *= 360.0f;
	zone = f / 60.0f;
	x = (1.0f - fabsf(fmodf(zone, 2.0f) - 1.0f));

	if (zone >= 0 && zone < 1)
		return (rgb_to_rgb_int(1.0f, x, 0.0f));
	if (zone >= 1 && zone < 2)
		return (rgb_to_rgb_int(x, 1.0f, 0.0f));
	if (zone >= 2 && zone < 3)
		return (rgb_to_rgb_int(0.0f, 1.0f, x));
	if (zone >= 3 && zone < 4)
		return (rgb_to_rgb_int(0.0f, x, 1.0f));
	if (zone >= 4 && zone < 5)
		return (rgb_to_rgb_int(x, 0.0f, 1.0f));
	return (rgb_to_rgb_int(1.0f, 0.0f, x));
}


static inline t_rgb_int depth_to_rgb_int(int depth, int total_depth)
{
	float		t;

	t = (float)(depth) / (float)total_depth;
	return (float_to_rainbow(fmodf(t, 1.0f)));
}

void	full_render(t_aabb_bvh *bvh, int target_depth, int total_depth, t_data *data)
{
	t_rgb_int	rgb;

	rgb = depth_to_rgb_int(target_depth + data->params.bvh_color_offset, total_depth);
	rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, rgb);
	if (bvh->depth > 0)
	{
		full_render(bvh->next_a, target_depth - 1, total_depth, data);
		full_render(bvh->next_b, target_depth - 1, total_depth, data);
	}
}

void	rasterize_bvh(t_aabb_bvh *bvh, t_params *p, int total_depth, t_data *data)
{
	t_rgb_int	rgb;
	t_rgb_int	color;

	rgb = depth_to_rgb_int(p->bvh_depth + data->params.bvh_color_offset, total_depth);
	color.r = rgb.r;
	color.g = rgb.g;
	color.b = rgb.b;
	if (p->bvh_depth == -1)
	{
		full_render(bvh, total_depth, total_depth, data);
		return ;
	}
	if (bvh->depth > p->bvh_depth)
	{
		rasterize_bvh(bvh->next_a, p, total_depth, data);
		rasterize_bvh(bvh->next_b, p, total_depth, data);
	}
	else
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, color);
}

void	rasterize_sphere_bvh(t_sphere_bvh *bvh, t_params *p, int total_depth, t_data *data)
{
	t_rgb_int	rgb;
	t_rgb_int	color;

	rgb = depth_to_rgb_int(p->bvh_depth + data->params.bvh_color_offset, total_depth);
	color.r = rgb.r;
	color.g = rgb.g;
	color.b = rgb.b;
	// if (p->bvh_depth == -1)
	// {
	// 	//full_render(bvh, total_depth, total_depth, data);
	// 	return ;
	// }
	if (bvh->depth > p->bvh_depth && p->bvh_depth >= 0)
	{
		rasterize_sphere_bvh(bvh->next_a, p, total_depth, data);
		rasterize_sphere_bvh(bvh->next_b, p, total_depth, data);
	}
	else
	{
		t_sphere	sphere;
		sphere.diameter = bvh->size * 2;
		sphere.pos = bvh->pos;
		rasterize_sphere(&sphere, &data->mlx->img, &data->scene.camera, color);
	}
}

