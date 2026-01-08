/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 05:16:58 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/04 05:16:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_types.h"
#include "minirt.h"
#include "calc.h"
#include "mlx_draw.h"
#include "rgb_operations.h"
#include "rgb_scalar.h"
#include "vec3_operations.h"
#include "vec3_special1.h"

void	normal_debug(t_buffers *buffers, int pixel)
{
	t_ray	*ray;

	ray = &buffers->rays[buffers->hits[pixel].id];
	ray->accumulated_color = rgb_add_scalar(rgb_scale(
				buffers->hits[pixel].normal,
				0.5f),
			0.5f);
	ray->through_power = rgb(0, 0, 0);
	buffers->hits[pixel].hit = false;
}

void	normal_debug_loop(t_buffers *buffers, int count)
{
	int	pixel;

	pixel = 0;
	while (pixel < count)
	{
		normal_debug(buffers, pixel);
		++pixel;
	}
}
