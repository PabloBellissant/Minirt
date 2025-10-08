/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:23:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/08 02:27:13 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>
#include "render.h"

int	hit_cylinder(t_ray *ray, t_object *o, float *t);

int hit_cylinder(t_ray *ray, t_object *o, float *t_out)
{
	t_vec3 oc = vec3_sub(ray->pos, o->cylinder.pos);
	float card = vec3_dot(o->cylinder.rot, ray->dir);
	float caoc = vec3_dot(o->cylinder.rot, oc);

	t_vec3 xdir = vec3_sub(ray->dir, vec3_scale(o->cylinder.rot, card));
	t_vec3 xoc  = vec3_sub(oc, vec3_scale(o->cylinder.rot, caoc));

	float A = vec3_dot(xdir, xdir);
	float B = 2.0f * vec3_dot(xdir, xoc);
	float C = vec3_dot(xoc, xoc) - o->cylinder.radius * o->cylinder.radius;
	float discriminant = B * B - 4 * A * C;

	if (discriminant < 0)
		return (0);

	float sqrtD = sqrtf(discriminant);
	float tmin = FLT_MAX;
	for (int k = 0; k < 2; k++) {
		float t = (-B + (k == 0 ? -sqrtD : sqrtD)) / (2.0f * A);
		if (t > 1e-4f) {
			float y = caoc + t * card;
			if (y >= 0.0f && y <= o->cylinder.height && t < tmin)
				tmin = t;
		}
	}

	*t_out = tmin;
	return (tmin < FLT_MAX);
}

