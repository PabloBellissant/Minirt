/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3i_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:01:15 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:28:54 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3I_OPERATIONS_H
# define VEC3I_OPERATIONS_H

# include "vectors_types.h"

static inline t_vec3i	vec3i(const int x, const int y, const int z)
{
	return ((t_vec3i){{x, y, z}});
}

static inline t_vec3i	vec3i_add(const t_vec3i a, const t_vec3i b)
{
	return ((t_vec3i){{a.x + b.x, a.y + b.y, a.z + b.z}});
}

static inline t_vec3i	vec3i_sub(const t_vec3i a, const t_vec3i b)
{
	return ((t_vec3i){{a.x - b.x, a.y - b.y, a.z - b.z}});
}

static inline t_vec3i	vec3i_mult(const t_vec3i a, const t_vec3i b)
{
	return ((t_vec3i){{a.x * b.x, a.y * b.y, a.z * b.z}});
}

#endif