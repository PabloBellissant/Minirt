/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_special2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:10:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 22:54:20 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include "colors_types.h"
# include "rgb_scalar.h"
# include "rgb_special1.h"

static const float INV_255 = 1.0f / 255.0f;

static inline uint8_t	clamp_float_to_byte(float val)
{
	int	temp;

	temp = (int)(val * 255.0f);
	if (temp > 255)
		return (255);
	if (temp < 0)
		return (0);
	return ((uint8_t)temp);
}

/*
	Function that convert `t_rgb` to `t_rgb_int`
	and clamps the result between 0 and 255
*/
static inline t_rgb_int	rgb_ftoi(const t_rgb rgb)
{
	return ((t_rgb_int){{{
		clamp_float_to_byte(rgb.b),
		clamp_float_to_byte(rgb.g),
		clamp_float_to_byte(rgb.r)
	}}});
}

/*
	Function that convert `t_rgb_int` to `t_rgb`
	and clamps the result between 0.f and 1.f
*/
static inline t_rgb rgb_itof(const t_rgb_int rgb)
{
    return (rgb_clamp((t_vec3){{{
        (float)rgb.b * INV_255,
        (float)rgb.g * INV_255,
        (float)rgb.r * INV_255
    }}}, 0.f, 1.f));
}

static inline t_rgb get_real_ratio(const t_rgb_int rgb, float ratio)
{
    return (rgb_clamp(rgb_scale((t_vec3){{{
        (float)rgb.b * INV_255,
        (float)rgb.g * INV_255,
        (float)rgb.r * INV_255
    }}}, ratio), 0.f, 1.f));
}

#endif