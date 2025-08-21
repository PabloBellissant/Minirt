/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_reg_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:35:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/22 02:38:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "calc.h"

static inline int	hit_plane(t_ray *restrict ray,
	t_plane *restrict p, float *t, t_vec3 normal);

t_object	*hit_reg_plane(t_ray *ray, t_scene *scene, float t_min)
{
	t_object	*obj;
	t_object	*res;
	float		t;
	int			i;

	obj = scene->planes;
	res = NULL;
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(ray, &obj[i].plane, &t, obj[i].plane.normal))
		{
			if (t < t_min)
			{
				t_min = t;
				res = &obj[i];
			}
		}
		++i;
	}
	if (!res)
		return (NULL);
	res->t = t_min;
	return (res);
}

static inline int	hit_plane(t_ray *restrict ray,
	t_plane *restrict p, float *t, t_vec3 normal)
{
	float	denom;

	denom = vec3_dot(ray->dir, normal) + FLT_MIN;
	*t = vec3_dot(vec3_sub(p->pos, ray->pos), normal) / denom;
	return (*t >= 0);
}

