/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:26:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 00:25:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <float.h>
#include "bvh.h"
#include "render.h"
#include "calc.h"

int	create_root_bvh(t_vector *bvh, t_vector *objects)
{
	t_aabb_bvh	root_bvh;

	ft_bzero(&root_bvh, sizeof(t_aabb_bvh));
	root_bvh.min = (t_vec3){{FLT_MAX, FLT_MAX, FLT_MAX}};
	root_bvh.max = (t_vec3){{-FLT_MAX, -FLT_MAX, -FLT_MAX}};
	set_size(&root_bvh, objects);
	vector_add(bvh, &root_bvh, 1);
	return (0);
}

int	fill_pointer(t_vector *object_vec, t_vector *pointer_vec)
{
	size_t		i;
	t_object	*object;
	t_object	*actual;

	vector_init(pointer_vec, sizeof(t_object *));
	object = object_vec->data;
	i = 0;
	while (i < object_vec->num_elements)
	{
		actual = &object[i];
		if (actual->type != PLANE && actual->type != LIGHT)
		{
			if (vector_add(pointer_vec, &actual, 1) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

void	cut_bvh_leaf(t_aabb_bvh *bvh)
{
	if (bvh->depth == 1)
	{
		bvh->object_a = bvh->next_a->object_a;
		bvh->object_b = bvh->next_b->object_a;
	}
	if (bvh->depth > 1)
	{
		cut_bvh_leaf(bvh->next_a);
		cut_bvh_leaf(bvh->next_b);
	}
}

int	create_aabb_bvh(t_scene *scene)
{
	t_vector	bvh_vec;
	size_t		volume_count;
	t_vector	objects_pointer;

	volume_count = get_bvh_count(&scene->objects);
	vector_init(&bvh_vec, sizeof(t_aabb_bvh));
	if (set_vector_size(&bvh_vec, volume_count) != 0)
		return (-1);
	if (fill_pointer(&scene->objects, &objects_pointer) != 0)
	{
		free_vector(&bvh_vec);
		return (-1);
	}
	create_root_bvh(&bvh_vec, &objects_pointer);
	if (volume_count > 1)
		subdivide(get_last_vector_value(&bvh_vec), &bvh_vec, &objects_pointer);
	scene->bvh.aabb_bvh = bvh_vec.data;
	cut_bvh_leaf(scene->bvh.aabb_bvh);
	return (0);
}
