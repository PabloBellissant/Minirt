/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:26:50 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/25 22:47:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

t_object	*create_object(t_scene *scene, t_object_type type)
{
	t_object	object;

	if (scene->objects.max_elements == 0)
		vector_init(&scene->objects, sizeof(t_object));
	ft_bzero(&object, sizeof(t_object));
	object.type = type;
	object.object_id = scene->objects.num_elements;
	if (vector_add(&scene->objects, &object, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->objects));
}
