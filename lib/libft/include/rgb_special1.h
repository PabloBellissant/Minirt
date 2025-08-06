/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_special1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:12:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 08:13:41 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_SPECIAL1_H
# define RGB_SPECIAL1_H

# include "colors_types.h"
# include "vec3_special1.h"
# include "vec3_special2.h"

static inline float	rgb_dot(const t_rgb a, const t_rgb b)
{
	return (vec3_dot(a, b));
}

static inline t_rgb	rgb_clamp(const t_rgb v, const float mn, const float mx)
{
	return (vec3_clamp(v, mn, mx));
}

static inline t_rgb	rgb_normalize(const t_rgb v)
{
	return (vec3_normalize(v));
}

static inline t_rgb	rgb_lerp(const t_rgb a, const t_rgb b, const float t)
{
	return (vec3_lerp(a, b, t));
}

#endif