/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:42:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/02 12:42:20 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_skybox(int pixel, t_buffers bu, int texture_id, t_texture *texture)
{
	t_rgb	color;

	color = sample_texture(texture, texture_id, bu.hits[pixel].uv);
	bu.addr[bu.hits[pixel].id] = rgb_ftoi(color).rgb;
}
