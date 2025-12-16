/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:51 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 19:00:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_on_screen(t_ray *rays, int *addr, int pixel, int pixel_size)
{
	t_vec2i		cube;
	t_rgb_int	color;

	cube.y = 0;
	while (cube.y < pixel_size)
	{
		cube.x = 0;
		while (cube.x < pixel_size)
		{
			color = rgb_ftoi(rays[pixel].accumulated_color);
			addr[pixel + (cube.y * WIDTH + cube.x)] = color.rgb;
			++cube.x;
		}
		++cube.y;
	}
}

