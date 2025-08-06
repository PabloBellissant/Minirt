/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_special2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:08:56 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:13:57 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_SPECIAL2_H
# define VEC3_SPECIAL2_H

# include <math.h>
# include "vectors_types.h"
# include "vec3_special1.h"

/*
	Normalize with zero-check to avoid division by zero
	Returns original vector if length is zero for safety
*/
static inline t_vec3	vec3_normalize(const t_vec3 v)
{
	float	len;

	len = vec3_length(v);
	if (len == 0.0f)
		return (v);
	return (vec3_scale(v, 1.0f / len));
}

static inline t_vec3 fast_vec3_normalize(const t_vec3 v)
{
    float len_sq = vec3_length2(v);
    if (len_sq == 0.0f)
        return v;
    
    // Fast reciprocal square root approximation + Newton-Raphson iteration
    float inv_len = 1.0f / sqrtf(len_sq);
    return vec3_scale(v, inv_len);
}

static inline float clamp_branchless(const float val, const float min, const float max)
{
    return fminf(fmaxf(val, min), max);
}

static inline t_vec3	vec3_clamp(const t_vec3 v, const float mn, const float mx)
{
    return (t_vec3){{{
        clamp_branchless(v.x, mn, mx),
        clamp_branchless(v.y, mn, mx),
        clamp_branchless(v.z, mn, mx)
	}}};
}


#endif