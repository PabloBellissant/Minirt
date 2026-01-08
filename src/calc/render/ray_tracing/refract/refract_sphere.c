/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:21:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/21 02:21:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_vec3	vec3_refract(t_vec3 ray_dir, t_vec3 normal, float eta);
float	get_sphere_t_out(t_ray *ray, t_object *o);

void	refract_sphere(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
	float	t_out;
	t_ray	temp;

	*dir = vec3_refract(*dir, hit->normal, 1.0f / ni);
	temp.origin = hit->hit_point;
	temp.dir = *dir;
	*origin = temp.origin;
	t_out = get_sphere_t_out(&temp, hit->hit_obj);
	*origin = vec3_add(*origin, vec3_scale(*dir, t_out + EPSILON));
	*dir = vec3_refract(
			*dir, vec3_normalize(
				vec3_sub(hit->hit_obj->sphere.pos, *origin)), ni / 1.0f);
}
