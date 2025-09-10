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

//ps: fait avec chat gepetto parce que vasy j'ai pas que ca a foutre
//de faire des fonctions pour simuler les couleurs de l'arc en ciel
//ces grands morts
static inline t_rgb hsv_to_rgb(float h, float s, float v)
{
	float r, g, b;

	h = fmodf(h, 1.0f) * 6.0f; // normalized hue cycle (0..6)
	int i = (int)floorf(h);
	float f = h - i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);

	switch (i % 6) {
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
		default: r = g = b = 0; break; // never happens
	}
	return rgb(r, g, b);
}

/* Map a depth level to an RGBA with depth ↔ rainbow color + transparency */
static inline t_rgba_int depth_to_rgba_int(int depth, int total_depth)
{
	if (total_depth <= 0)
		return rgba_int(255, 255, 255, 255); // fallback white opaque

	float t = (float)(depth) / (float)total_depth;  
	// Hue: vary across 0..1 spectrum based on depth
	float hue = t;  
	t_rgb col = hsv_to_rgb(hue, 1.0f, 1.0f);

	// Alpha: semi-transparent at max depth, more transparent at leafs
	// Example: root = 0.7, leaf = 0.2
	float alpha = 0.2f + 0.5f * t;  

	return rgba_int(
		(uint8_t)(col.data[COL_R] * 255.0f),
		(uint8_t)(col.data[COL_G] * 255.0f),
		(uint8_t)(col.data[COL_B] * 255.0f),
		(uint8_t)(alpha * 255.0f)
	);
}

void	rasterize_bvh(t_bvh *bvh, t_params *p, int total_depth, t_data *data)
{
	t_rgba_int	rgba;
	t_rgb_int	color;

	rgba = depth_to_rgba_int(bvh->depth + data->params.bvh_color_offset + 1, total_depth);
	color.r = rgba.r;
	color.g = rgba.g;
	color.b = rgba.b;
	if (p->bvh_depth == -1)
	{
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, color);
		if (bvh->depth > 0)
		{
			rasterize_bvh(bvh->next_a, p, total_depth, data);
			rasterize_bvh(bvh->next_b, p, total_depth, data);
		}
	}
	else if (bvh->depth > p->bvh_depth)
	{
		rasterize_bvh(bvh->next_a, p, total_depth, data);
		rasterize_bvh(bvh->next_b, p, total_depth, data);
	}
	else
		rasterize_cuboid(&bvh->cuboid, &data->mlx->img, &data->scene.camera, color);
}

