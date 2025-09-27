/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_supersampling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 04:44:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 04:44:24 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_supersampling(t_bound *bound, t_vec2i force, t_img_data *img)
{
	t_vec2i	pixel;

	if (force.x == 1 && force.y == 1)
		return ;
	pixel.x = bound->left;
	while (pixel.x < bound->right)
	{
		pixel.y = bound->top;
		while (pixel.y < bound->down)
		{
			ft_mlx_pixel_put(img, pixel, 0xFF00FF);
			if (pixel.x < bound->right - force.x / 2
				&& pixel.y < bound->down - force.y / 2)
			{
				ft_mlx_pixel_put(img, (t_vec2i)
				{{pixel.x + force.x / 2, pixel.y + force.y / 2}}, 0xFF00FF);
			}
			pixel.y += force.y;
		}
		pixel.x += force.x;
	}
}
