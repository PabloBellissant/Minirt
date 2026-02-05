/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_by_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:25:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/19 15:25:35 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "render.h"
#include "parsing.h"

static int	fill_plane_type(t_scene *scene);

int	fill_by_type(t_opencl *state, t_scene *scene)
{
	if (fill_plane_type(scene) == -1)
		return (-1);
	if (fill_gpu_data(state, scene) == -1)
		return (-1);
	return (0);
}

static int	fill_plane_type(t_scene *scene)
{
	t_vector	plane_vec;
	size_t		i;
	t_object	*object;

	vector_init(&plane_vec, sizeof(int));
	object = scene->objects.data;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type == PLANE)
		{
			if (vector_add(&plane_vec, &i, 1) == -1)
			{
				free_vector(&plane_vec);
				return (-1);
			}
		}
		++i;
	}
	scene->planes_id = plane_vec.data;
	scene->plane_count = (int)plane_vec.num_elements;
	return (0);
}
