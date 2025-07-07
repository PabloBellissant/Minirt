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

static int		create_object_bvh(t_scene *scene, t_vector *bvh_vec);
static void		set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *size);
bool			is_bvh_full(t_vector *bvh_vec);
t_bvh			*get_root(t_vector *bvh_vec);

int	create_bvh(t_scene *scene)
{
	t_vector	bvh_vec;

	vector_init(&bvh_vec, sizeof(t_bvh));
	if (create_object_bvh(scene, &bvh_vec) == -1)
		return (-1);
	while (is_bvh_full(&bvh_vec) == false)
	{
		if (merge_nearest_bvh(&bvh_vec) == -1)
		{
			free_vector(&bvh_vec);
			return (-1);
		}
	}
	scene->bvh = get_root(&bvh_vec);
	return (0);
}

t_bvh	*get_root(t_vector *bvh_vec)
{
	size_t	i;
	t_bvh	*bvh;

	bvh = bvh_vec->data;
	i = 0;
	while (bvh[i].parent != NULL)
		++i;
	return (&bvh[i]);
}

bool	is_bvh_full(t_vector *bvh_vec)
{
	size_t	i;
	t_bvh	*bvh;
	int		orphin_count;

	bvh = bvh_vec->data;
	orphin_count = 0;
	i = 0;
	while (i < bvh_vec->num_elements)
	{
		if (bvh[i].parent == NULL)
			++orphin_count;
		if (orphin_count == 2)
			return (false);
		++i;
	}
	return (true);
}

static int	create_object_bvh(t_scene *scene, t_vector *bvh_vec)
{
	t_bvh		single_bvh;
	t_object	*actual_object;

	single_bvh.parent = NULL;
	single_bvh.depth = 0;
	while (bvh_vec->num_elements < scene->objects.num_elements)
	{
		actual_object = get_vector_value(&scene->objects, bvh_vec->num_elements);
		set_bvh_size(actual_object, &single_bvh.pos, &single_bvh.size);
		single_bvh.object = actual_object;
		if (vector_add(bvh_vec, &single_bvh, 1) == -1)
		{
			free_vector(bvh_vec);
			return (-1);
		}
	}
	return (0);
}

static void	set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *size)
{
	t_triangle	t;

	if (object->type == SPHERE)
	{
		pos->x = object->sphere.pos.x - (object->sphere.diameter / 2);
		pos->y = object->sphere.pos.y - (object->sphere.diameter / 2);
		pos->z = object->sphere.pos.z - (object->sphere.diameter / 2);
		size->x = object->sphere.diameter;
		size->y = object->sphere.diameter;
		size->z = object->sphere.diameter;
	}
	if (object->type == TRIANGLE)
	{
		t = object->triangle;
		pos->x = ft_minf(ft_minf(t.p0.pos.x, t.p1.pos.x), t.p2.pos.x);
		pos->y = ft_minf(ft_minf(t.p0.pos.y, t.p1.pos.y), t.p2.pos.y);
		pos->z = ft_minf(ft_minf(t.p0.pos.z, t.p1.pos.z), t.p2.pos.z);
		size->x = ft_maxf(ft_maxf(t.p0.pos.x, t.p1.pos.x), t.p2.pos.x);
		size->y = ft_maxf(ft_maxf(t.p0.pos.y, t.p1.pos.y), t.p2.pos.y);
		size->z = ft_maxf(ft_maxf(t.p0.pos.z, t.p1.pos.z), t.p2.pos.z);
	}
}
