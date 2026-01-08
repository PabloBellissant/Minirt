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

#include "render.h"
#include "vec3_special1.h"


int	fill_plane_type(t_scene *scene);
int	fill_emissive_type(t_scene *scene);

int	fill_by_type(t_scene *scene)
{
	if (fill_plane_type(scene) == -1)
		return (-1);
	if (fill_emissive_type(scene) == -1)
		return (-1); // should free here instead of main
	return (0);
}

int	fill_plane_type(t_scene *scene)
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

int	fill_emissive_type(t_scene *scene)
{
	t_vector	emissive_vec;
	size_t		i;
	t_object	*object;
	t_mat		*mat;

	vector_init(&emissive_vec, sizeof(int));
	object = scene->objects.data;
	mat = scene->mat.data;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type != PLANE \
			&& vec3_length2(mat[object[i].mat_id].ke) > 0.001f)
		{
			if (vector_add(&emissive_vec, &i, 1) == -1)
			{
				free_vector(&emissive_vec);
				return (-1);
			}
		}
		++i;
	}
	scene->emissive_id = emissive_vec.data;
	scene->emissive_count = (int)emissive_vec.num_elements;
	return (0);
}
