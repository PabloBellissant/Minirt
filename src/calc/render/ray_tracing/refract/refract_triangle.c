/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:19:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/21 02:19:40 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_vec3	vec3_refract(t_vec3 ray_dir, t_vec3 normal, float eta);
t_vec3	vec3_negate(t_vec3 v);

void	refract_triangle(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
	float	cos_theta;

	cos_theta = vec3_dot(*dir, hit->normal);
	if (cos_theta < 0.0f)
		*dir = vec3_refract(*dir, hit->normal, 1.0f / ni);
	else
		*dir = vec3_refract(*dir, vec3_negate(hit->normal), ni / 1.0f);
	*origin = vec3_add(hit->hit_point, vec3_scale(*dir, EPSILON));
}

t_vec3	vec3_negate(t_vec3 v)
{
	t_vec3	res;

	res.x = -v.x;
	res.y = -v.y;
	res.z = -v.z;
	return (res);
}
