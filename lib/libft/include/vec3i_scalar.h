/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3i_scalar.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:09:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:29:46 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3I_SCALAR_H
# define VEC3I_SCALAR_H

# include "vectors_types.h"

static inline t_vec3i	vec3i_scale(const t_vec3i v, const int s)
{
	return ((t_vec3i){{v.x * s, v.y * s, v.z * s}});
}

static inline t_vec3i	vec3i_add_scalar(const t_vec3i v, const int s)
{
	return ((t_vec3i){{v.x + s, v.y + s, v.z + s}});
}

static inline t_vec3i	vec3i_sub_scalar(const t_vec3i v, const int s)
{
	return ((t_vec3i){{v.x - s, v.y - s, v.z - s}});
}

#endif