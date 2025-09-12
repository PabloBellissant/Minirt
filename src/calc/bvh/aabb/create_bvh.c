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
#include <math.h>
#include "bvh.h"
#include "render.h"

static int		create_object_bvh(t_scene *scene, t_vector *bvh_vec);
static void		set_bvh_size(t_object *object, t_vec3 *min, t_vec3 *max);

int	init_aabb_bvh(t_vector *bvh_vec, t_scene *scene)
{
	size_t		volume_count;

	vector_init(bvh_vec, sizeof(t_aabb_bvh));
	volume_count = get_bvh_count(&scene->objects);
	if (set_vector_size(bvh_vec, volume_count) != 0)
		return (-1);
	return (0);
}

int	create_aabb_bvh(t_scene *scene)
{
	t_vector	bvh_vec;
	int			*parents;

	if (init_aabb_bvh(&bvh_vec, scene) == -1)
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
	scene->bvh.aabb_bvh = get_aabb_root(&bvh_vec, parents);
	free(parents);
	return (0);
}

static int	create_object_bvh(t_scene *scene, t_vector *bvh_vec)
{
	t_aabb_bvh		single_bvh;
	t_object	*object;
	size_t		i;

	ft_bzero(&single_bvh, sizeof(t_aabb_bvh));
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

static void	set_bvh_size(t_object *object, t_vec3 *min, t_vec3 *max)
{
	if (object->type == SPHERE)
	{
		min->x = object->sphere.pos.x - (object->sphere.diameter / 2);
		min->y = object->sphere.pos.y - (object->sphere.diameter / 2);
		min->z = object->sphere.pos.z - (object->sphere.diameter / 2);
		max->x = min->x + object->sphere.diameter;
		max->y = min->y + object->sphere.diameter;
		max->z = min->z + object->sphere.diameter;
	}
	if (object->type == CYLINDER)
	{
		min->x = object->cylinder.pos.x - fmaxf(object->cylinder.radius, object->cylinder.height);
		min->y = object->cylinder.pos.y - fmaxf(object->cylinder.radius, object->cylinder.height);
		min->z = object->cylinder.pos.z - fmaxf(object->cylinder.radius, object->cylinder.height);
		max->x = min->x + fmaxf(object->cylinder.radius, object->cylinder.height) * 2;
		max->y = min->y + fmaxf(object->cylinder.radius, object->cylinder.height) * 2;
		max->z = min->z + fmaxf(object->cylinder.radius, object->cylinder.height) * 2;
	}
}
