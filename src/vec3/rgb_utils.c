/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:07:29 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/05 05:02:51 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_rgb	*get_real_ratio(const t_color *color, const float ratio, t_rgb *rgb)
{
	rgb->x = (float)color->r / 255.0f;
	rgb->y = (float)color->g / 255.0f;
	rgb->z = (float)color->b / 255.0f;
	return (vec3_scale(rgb, ratio));
}

t_rgb	*rgb_clamp(t_rgb *rgb, float min, float max)
{
	float	*_rgb[3];
	size_t	i;

	_rgb[0] = &(rgb->r);
	_rgb[1] = &(rgb->g);
	_rgb[2] = &(rgb->b);
	i = 0;
	while (i < 3)
	{
		if (*(_rgb[i]) < min)
			*(_rgb[i]) = min;
		else if (*(_rgb[i]) > max)
			*(_rgb[i]) = max;
		i++;
	}
	return (rgb);
}

t_color	*rgb_to_color(const t_rgb *rgb, t_color *col)
{
	int	temp;

	temp = rgb->r * 255;
	if (temp > 255)
		col->r = 255;
	else if (temp < 0)
		col->r = 0;
	else
		col->r = temp;
	temp = rgb->g * 255;
	if (temp > 255)
		col->g = 255;
	else if (temp < 0)
		col->g = 0;
	else
		col->g = temp;
	temp = rgb->b * 255;
	if (temp > 255)
		col->b = 255;
	else if (temp < 0)
		col->b = 0;
	else
		col->b = temp;
	return (col);
}
