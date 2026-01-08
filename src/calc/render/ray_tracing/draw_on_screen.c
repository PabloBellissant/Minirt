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

#include "minirt.h"
#include "mlx_draw.h"
#include "render.h"
#include "rgb_operations.h"
#include "rgb_scalar.h"

void	draw_on_screen(t_ray *rays, t_img_data *img, int pixel, int pixel_size)
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
			if (cube.x + pixel % img->width < img->width
				&& cube.y + pixel / img->width < img->height)
			{
				img->addr[pixel + (cube.y * img->width + cube.x)] = color.rgb;
			}
			++cube.x;
		}
		++cube.y;
	}
}

void	accu_on_screen(t_buffers bu, int pixel, int sample_count)
{
	t_rgb_int	color;

	bu.accu[pixel] = rgb_add(bu.accu[pixel], bu.rays[pixel].accumulated_color);
	color = rgb_ftoi(rgb_div_scalar(bu.accu[pixel], sample_count));
	bu.addr[pixel] = color.rgb;
}

void	draw_screen_loop(t_ray *rays, t_img_data *img, int pixel_size)
{
	t_vec2i	pixel;

	pixel.y = 0;
	while (pixel.y < img->height)
	{
		pixel.x = 0;
		while (pixel.x < img->width)
		{
			draw_on_screen(rays, img,
				(pixel.y * img->width + pixel.x), pixel_size);
			pixel.x += pixel_size;
		}
		pixel.y += pixel_size;
	}
}

void	accu_screen_loop(t_buffers bu, int sample_count, t_img_data *img)
{
	t_vec2i	pixel;

	pixel.y = 0;
	while (pixel.y < img->height)
	{
		pixel.x = 0;
		while (pixel.x < img->width)
		{
			accu_on_screen(bu, (pixel.y * img->width + pixel.x), sample_count);
			++pixel.x;
		}
		++pixel.y;
	}
}
