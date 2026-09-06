/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:38:10 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/09 01:10:11 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

#define POINT_EPSILON 1e-6f

static inline t_vec3	rotate_around_axis(const t_vec3 p, const t_vec3 u,
							const float cos_theta, const float sin_theta)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	term1 = vec3_scale(p, cos_theta);
	term2 = vec3_scale(u, vec3_dot(u, p) * (1 - cos_theta));
	term3 = vec3_scale(vec3_cross(u, p), sin_theta);
	return (vec3_add(vec3_add(term1, term2), term3));
}

t_vec3	rotate_point(const t_vec3 pos, t_vec3 rot)
{
	const t_vec3	z_axis = vec3(0, 0, 1);
	t_vec3			rotation_axis;
	float			angle;

	rot = vec3_normalize(rot);
	if ((fabsf(rot.x) < POINT_EPSILON) && (fabsf(rot.y) < POINT_EPSILON))
		return (pos);
	rotation_axis = vec3_cross(z_axis, rot);
	rotation_axis = vec3_normalize(rotation_axis);
	angle = acosf(vec3_dot(z_axis, rot));
	return (rotate_around_axis(pos, rotation_axis, cosf(angle), sinf(angle)));
}
