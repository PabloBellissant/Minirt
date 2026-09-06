/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_global_bvh.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 05:27:31 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/17 11:57:26 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "bvh_shape.h"
#include "bvh_splitting.h"
#include "parsing.h"

static inline int	add_triangle(t_vector *prim, t_vector *ret, t_object *ob)
{
	size_t	i;

	i = 0;
	while (i < prim->num_elements)
	{
		if (ob[i].type == TRIANGLE)
		{
			ob[i].type = TRIANGLE;
			ob[i].object_id = ret->num_elements;
			if (vector_add(ret, &ob[i], 1) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static inline int	clean_prim(t_vector *prim, t_vector *new)
{
	size_t		i;
	t_object	*objects;

	vector_init(new, sizeof(t_object));
	objects = prim->data;
	i = 0;
	while (i < prim->num_elements)
	{
		if (objects[i].type == SPHERE)
		{
			objects[i].object_id = new->num_elements;
			objects[i].type = SPHERE;
			if (vector_add(new, &objects[i], 1) == -1)
				return (-1);
		}
		++i;
	}
	if (add_triangle(prim, new, objects) == -1)
		return (-1);
	return (0);
}

static inline size_t	get_sphere_count(t_vector prim)
{
	size_t		i;
	size_t		count;
	t_object	*object;

	object = prim.data;
	count = 0;
	i = 0;
	while (i < prim.num_elements)
	{
		if (object[i].type == SPHERE)
			++count;
		++i;
	}
	return (count);
}

static inline void	set_type(t_vector prim, t_bvh_header *bvh_header)
{
	size_t		i;
	t_bvh_node	*nodes;
	t_object	*primitives;
	size_t		sphere_count;

	sphere_count = get_sphere_count(prim);
	primitives = prim.data;
	nodes = bvh_header->nodes.data;
	i = 0;
	while (i < bvh_header->nodes.num_elements)
	{
		if (nodes[i].children[0] <= 0)
		{
			nodes[i].type = primitives[nodes[i].object_id].type;
			if (nodes[i].type == TRIANGLE)
				nodes[i].object_id -= sphere_count;
		}
		++i;
	}
}

void	debug_bvh_tree(t_bvh_header *h);

int	create_global_bvh(t_bvh_header **bvh_header, t_vector primitives)
{
	int			ret;
	t_vector	prim;

	*bvh_header = ft_calloc(1, sizeof(t_bvh_header));
	if (!*bvh_header)
		return (1);
	if (clean_prim(&primitives, &prim) == -1)
		return (-1);
	ret = create_bvh(*bvh_header, BVH_OBB, SAH, prim);
	if (ret)
	{
		free(bvh_header);
		return (1);
	}
	set_type(prim, *bvh_header);
	index_bvh(**bvh_header);
	debug_bvh_tree(*bvh_header);
	free_vector(&prim);
	return (ret);
}
