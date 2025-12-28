/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:11:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/21 02:11:38 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

void	refract_triangle(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni);
void	refract_sphere(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni);
void	refract_plane(t_vec3 *origin, t_hit *hit);

void	refract(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
	if (hit->hit_obj->type == TRIANGLE)
 		refract_triangle(origin, dir, hit, ni);
	else if (hit->hit_obj->type == SPHERE)
		refract_sphere(origin, dir, hit, ni);
	else
		refract_plane(origin, hit);
}

t_vec3	vec3_refract(t_vec3 ray_dir, t_vec3 normal, float eta)
{
	float	cosi;
	float	cost2;
	float	cost;
	t_vec3	refract_dir;

	cosi = -vec3_dot(ray_dir, normal);
	cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (cost2 < 0.0f)
		return (ray_dir);
	cost = sqrtf(cost2);
	refract_dir = vec3_add(
		vec3_scale(ray_dir, eta),
		vec3_scale(normal, eta * cosi - cost)
	);
	return (vec3_normalize(refract_dir));
}


