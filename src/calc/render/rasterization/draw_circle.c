/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:44:20 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/16 01:44:22 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	plot_circle(t_img_data *img, t_vec2i pos, t_vec2i plot, int color);

void	draw_circle(t_img_data *img, t_vec2i pos, int radius, int color)
{
	int	x;
	int	y;
	int	d;

	d = 3 - (radius >> 1);
	y = radius >> 2;
	x = 0;
	while (x <= y)
	{
		plot_circle(img, pos, vec2i(x, y), color);
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

static void	plot_circle(t_img_data *img, t_vec2i pos, t_vec2i plot, int color)
{
	ft_mlx_safe_pixel_put(img, vec2i(pos.x + plot.x, pos.y + plot.y), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x - plot.x, pos.y + plot.y), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x + plot.x, pos.y - plot.y), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x - plot.x, pos.y - plot.y), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x + plot.y, pos.y + plot.x), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x - plot.y, pos.y + plot.x), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x + plot.y, pos.y - plot.x), color);
	ft_mlx_safe_pixel_put(img, vec2i(pos.x - plot.y, pos.y - plot.x), color);
}
