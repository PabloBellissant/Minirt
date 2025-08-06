/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_operations.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:06:20 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 10:05:37 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_OPERATIONS_H
# define RGB_OPERATIONS_H

# include "colors_types.h"
# include "vec3_operations.h"

static inline t_rgb	rgb_add(const t_rgb a, const t_rgb b)
{
	return (vec3_add(a, b));
}

static inline t_rgb	rgb_sub(const t_rgb a, const t_rgb b)
{
	return (vec3_sub(a, b));
}

static inline t_rgb	rgb_mult(const t_rgb a, const t_rgb b)
{
	return (vec3_mult(a, b));
}

#endif