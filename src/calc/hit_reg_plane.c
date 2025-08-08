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

t_object	*hit_reg_plane(t_ray *ray, t_scene *scene)
{
	int			i;
	int			i_min;
	float		t_min;
	t_object	*object;
	float		t;

	object = scene->planes;
	t_min = FLT_MAX;
	i_min = -1;
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(ray, &object[i].plane, &t))
		{
			if (t < t_min)
			{
				i_min = i;
				t_min = t;
			}
		}
		++i;
	}
	if (i_min == -1)
		return (NULL);
	object[i_min].t = t_min;
	return (&object[i_min]);
}
