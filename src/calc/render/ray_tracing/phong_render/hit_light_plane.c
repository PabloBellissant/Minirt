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

t_rgb	hit_light_plane(t_ray *ray, t_scene *scene, float t_min, t_mat *mat)
{
	t_object	*obj;
	int			*plane_list;
	float		t;
	int			i;
	t_rgb		color;

	color = rgb(1, 1, 1);
	obj = scene->objects.data;
	plane_list = scene->planes_id;
	i = 0;
	while (i < scene->plane_count)
	{
		if (hit_plane(ray, &obj[plane_list[i]], &t))
		{
			if (t > 0.01f && t < t_min)
			{
				color = rgb_mult(color,
						rgb_scale(mat[obj[plane_list[i]].mat_id].kd, 1.0f
							- mat[obj[plane_list[i]].mat_id].opacity));
			}
		}
		++i;
	}
	return (color);
}
