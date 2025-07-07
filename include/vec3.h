/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 04:28:42 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/01 04:28:47 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "struct.h"

t_vec3	*vec3_add(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);
t_vec3	*vec3_sub(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);
t_vec3	*vec3_scale(t_vec3 *vec1, const float x);
t_vec3	*vec3_add_scalar(t_vec3 *vec, const float x);
t_vec3	*vec3_div_scalar(t_vec3 *vec, const float x);

float	vec3_length(const t_vec3 *v);
float	vec3_length_squared(const t_vec3 *v);
float	*vec3_dot(const t_vec3 *u, const t_vec3 *v, float *result);
t_vec3	*vec3_unit(t_vec3 *v);
t_vec3	*vec3_lerp(t_vec3 *a, t_vec3 *b, float t, t_vec3 *result);
t_vec3	*vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out);
//
//
//t_vec3*    vec3_cross(const t_vec3 u, const t_vec3 v);
//
//t_vec3*    vec3_fmax(t_vec3 a, t_vec3 b);
//t_vec3*    vec3_fmin(t_vec3 a, t_vec3 b);
//
//t_vec3*    vec3_negate(const t_vec3 v);
//t_vec3*    vec3_init(float x, float y, float z);
t_vec3	*vec3_random(t_vec3 *vec);

#endif
