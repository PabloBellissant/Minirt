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

#include "mlx_draw.h"
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
			if (cube.x + pixel % WIDTH < WIDTH && cube.y + pixel / WIDTH < HEIGHT)
				addr[pixel + (cube.y * WIDTH + cube.x)] = color.rgb;
			++cube.x;
		}
		++cube.y;
	}
}

void	draw_screen_loop(t_ray *rays, int *addr, int pixel_size)
{
	t_vec2i	pixel;

	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			draw_on_screen(rays, addr, (pixel.y * WIDTH + pixel.x), pixel_size);
			pixel.x += pixel_size;
		}
		pixel.y += pixel_size;
	}
}

