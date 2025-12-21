/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_light_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:35:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/22 02:38:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "calc.h"

int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t);

t_object	*hit_light_plane(t_ray *ray, t_scene *scene, float t_min)
{
	t_object	*obj;
	float		t;
	int			i;

	obj = scene->planes;
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(ray, &obj[i], &t))
		{
			if (t < t_min)
			{
				obj[i].t = t;
				return (obj + i);
			}
		}
		++i;
	}
	return (NULL);
}
