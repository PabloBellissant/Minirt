/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 06:31:17 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/30 06:31:41 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bvh.h"
#include "struct.h"

static int		create_object_bvh(t_scene *scene);
static void	set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *size);

int	create_bvh(t_scene *scene)
{
	create_object_bvh(scene);
}

static int	create_object_bvh(t_scene *scene)
{
	t_bvh		single_bvh;
	t_object	*actual_object;

	ft_bzero(&single_bvh, sizeof(t_bvh));
	vector_init(&scene->bvh, sizeof(t_bvh));
	while (scene->bvh.num_elements < scene->objects.num_elements)
	{
		actual_object = get_vector_value(&scene->objects, scene->bvh.num_elements);
		set_bvh_size(actual_object, &single_bvh.pos, &single_bvh.size);
		single_bvh.object = actual_object;
		if (vector_add(&scene->bvh, &single_bvh, 1) == -1)
		{
			free_vector(&scene->bvh);
			return (-1);
		}
	}
}

static void	set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *size)
{
	if (object->type == SPHERE)
	{
		pos->x = object->sphere.pos.x - object->sphere.diameter / 2;
		pos->y = object->sphere.pos.y - object->sphere.diameter / 2;
		pos->z = object->sphere.pos.z - object->sphere.diameter / 2;
		size->x = object->sphere.diameter;
		size->y = object->sphere.diameter;
		size->z = object->sphere.diameter;
	}
}
