/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_scalar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:11:54 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 08:12:17 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_SCALAR_H
# define RGB_SCALAR_H

# include "colors_types.h"
# include "vec3_scalar.h"

static inline t_rgb	rgb_scale(const t_rgb v, const float s)
{
	return (vec3_scale(v, s));
}

static inline t_rgb	rgb_add_scalar(const t_rgb v, const float s)
{
	return (vec3_add_scalar(v, s));
}

static inline t_rgb	rgb_sub_scalar(const t_rgb v, const float s)
{
	return (vec3_sub_scalar(v, s));
}

static inline t_rgb	rgb_div_scalar(const t_rgb v, const float s)
{
	return (vec3_div_scalar(v, s));
}
#endif