/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_rainbow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 06:49:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/11 06:49:43 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "colors_types.h"

t_rgb_int	rgb_to_rgb_int(float r, float g, float b);

t_rgb_int	float_to_rainbow(float f)
{
	float		zone;
	float		x;

	f *= 360.0f;
	zone = f / 60.0f;
	x = (1.0f - fabsf(fmodf(zone, 2.0f) - 1.0f));
	if (zone >= 0 && zone < 1)
		return (rgb_to_rgb_int(1.0f, x, 0.0f));
	if (zone >= 1 && zone < 2)
		return (rgb_to_rgb_int(x, 1.0f, 0.0f));
	if (zone >= 2 && zone < 3)
		return (rgb_to_rgb_int(0.0f, 1.0f, x));
	if (zone >= 3 && zone < 4)
		return (rgb_to_rgb_int(0.0f, x, 1.0f));
	if (zone >= 4 && zone < 5)
		return (rgb_to_rgb_int(x, 0.0f, 1.0f));
	return (rgb_to_rgb_int(1.0f, 0.0f, x));
}

t_rgb_int	rgb_to_rgb_int(float r, float g, float b)
{
	return ((t_rgb_int){{(uint8_t)(r * 255.0f + 0.5f),
		(uint8_t)(g * 255.0f + 0.5f), (uint8_t)(b * 255.0f + 0.5f)}});
}
