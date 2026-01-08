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

int	hit_plane(t_ray *restrict ray, t_object *restrict o, float *t);

t_object	*hit_reg_plane(t_ray *ray, t_scene *scene, float t_min)
{
	t_object	*obj;
	int			*plane_list;
	int			nearest;
	float		t;
	int			i;

	obj = scene->objects.data;
	plane_list = scene->planes_id;
	nearest = -1;
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(ray, &obj[plane_list[i]], &t))
		{
			if (t < t_min)
			{
				t_min = t;
				nearest = i;
			}
		}
		++i;
	}
	if (nearest == -1)
		return (NULL);
	obj = obj + plane_list[nearest];
	obj->t = t_min;
	return (obj);
}
