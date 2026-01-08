/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 23:48:20 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/01 23:48:20 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"

t_rgb	sample_texture(const t_texture *texture_list, int id, t_vec2 uv)
{
	int			x;
	int			y;
	t_rgb_int	color;
	int			offset;

	x = (int)(uv.u * (float)(texture_list[id].width));
	y = (int)(uv.v * (float)(texture_list[id].height));
	offset = y * texture_list[id].line_len + x * texture_list[id].channels;
	color.r = texture_list[id].pixels[offset + 0];
	color.g = texture_list[id].pixels[offset + 1];
	color.b = texture_list[id].pixels[offset + 2];
	return (rgb_itof(color));
}

float	sample_gray_level_texture(const t_texture *texture_list,
			int id, t_vec2 uv)
{
	int				x;
	int				y;
	int				offset;
	unsigned char	pixel;

	x = (int)(uv.u * (float)(texture_list[id].width));
	y = (int)(uv.v * (float)(texture_list[id].height));
	offset = y * texture_list[id].line_len + x;
	pixel = texture_list[id].pixels[offset];
	return ((float)pixel / 255.0f);
}
