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

int	fill_by_type(t_scene *scene)
{
	t_vector	plane_vec;
	size_t		i;
	t_object	*object;

	vector_init(&plane_vec, sizeof(t_object));
	object = scene->objects.data;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type == PLANE)
		{
			if (vector_add(&plane_vec, &object[i], 1) == -1)
			{
				free_vector(&plane_vec);
				return (-1);
			}
		}
		++i;
	}
	scene->planes = plane_vec.data;
	scene->plane_count = plane_vec.num_elements;
	return (0);
}
