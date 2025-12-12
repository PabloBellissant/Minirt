/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:42:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/12 01:17:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rgb_operations.h"
#include "rgb_scalar.h"

void	draw_skybox(int pixel, t_buffers bu, int texture_id, t_texture *texture)
{
	t_rgb	color;

	color = sample_texture(texture, texture_id, bu.hits[pixel].uv);
	bu.rays[bu.hits[pixel].id].accumulated_color = rgb_add(bu.rays[bu.hits[pixel].id].accumulated_color, rgb_mult(color, bu.rays[bu.hits[pixel].id].through_power));
}
