/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:26:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/17 02:26:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

t_object	*create_object(t_scene *scene, t_object_type type)
{
	t_object	object;

	if (scene->objects.max_elements == 0)
		vector_init(&scene->objects, sizeof(t_object));
	ft_bzero(&object, sizeof(t_object));
	object.type = type;
	if (vector_add(&scene->objects, &object, 1) == -1)
		return (NULL);
	return (get_vector_value(&scene->objects, scene->objects.num_elements - 1));
}
