/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 06:31:17 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:08:17 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include "bvh.h"
#include "render.h"

static int		create_object_bvh(t_scene *scene, t_vector *bvh_vec);
static void		set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *max);
bool			is_bvh_full(t_vector *bvh_vec, int *parents);
t_bvh			*get_root(t_vector *bvh_vec, int *parents);

int	init_bvh(t_vector *bvh_vec, t_scene *scene)
{
	size_t		volume_count;
	size_t		i;
	t_object	*object;

	vector_init(bvh_vec, sizeof(t_bvh));
	object = scene->objects.data;
	volume_count = 0;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type != PLANE && object[i].type != LIGHT)
			++volume_count;
		++i;
	}
	i = volume_count;
	while (i > 1)
	{
		volume_count += i / 2;
		i -= i / 2;
	}
	if (set_vector_size(bvh_vec, volume_count) != 0)
		return (-1);
	return (0);
}

int	create_bvh(t_scene *scene)
{
	t_vector	bvh_vec;
	int			*parents;

	if (init_bvh(&bvh_vec, scene) == -1)
		return (-1);
	parents = ft_calloc(bvh_vec.max_elements, sizeof(int));
	if (!parents)
	{
		free_vector(&bvh_vec);
		return (-1);
	}
	create_object_bvh(scene, &bvh_vec);
	while (is_bvh_full(&bvh_vec, parents) == false)
		merge_nearest_bvh(&bvh_vec, parents);
	scene->bvh = get_root(&bvh_vec, parents);
	return (0);
}

t_bvh	*get_root(t_vector *bvh_vec, int *parents)
{
	size_t		i;
	t_bvh		*bvh;

	bvh = bvh_vec->data;
	i = 0;
	while (parents[i] == 1)
		++i;
	return (&bvh[i]);
}

bool	is_bvh_full(t_vector *bvh_vec, int *parents)
{
	size_t	i;
	int		orphin_count;

	orphin_count = 0;
	i = 0;
	while (i < bvh_vec->num_elements)
	{
		if (parents[i] == 0)
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
	t_object	*object;
	size_t		i;

	ft_bzero(&single_bvh, sizeof(t_bvh));
	object = scene->objects.data;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type != PLANE && object[i].type != LIGHT)
		{
			set_bvh_size(&(object[i]), &single_bvh.min, &single_bvh.max);
			single_bvh.object = &(object[i]);
			vector_add(bvh_vec, &single_bvh, 1);
		}
		++i;
	}
	return (0);
}

static void	set_bvh_size(t_object *object, t_vec3 *pos, t_vec3 *max)
{
	if (object->type == SPHERE)
	{
		pos->x = object->sphere.pos.x - (object->sphere.diameter / 2);
		pos->y = object->sphere.pos.y - (object->sphere.diameter / 2);
		pos->z = object->sphere.pos.z - (object->sphere.diameter / 2);
		max->x = pos->x + object->sphere.diameter;
		max->y = pos->y + object->sphere.diameter;
		max->z = pos->z + object->sphere.diameter;
	}
}
