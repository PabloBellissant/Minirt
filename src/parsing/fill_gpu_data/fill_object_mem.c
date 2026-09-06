/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_object_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 02:08:08 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/14 02:08:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	init_vec_type(t_vector *vec, t_object_type type)
{
	if (type == TRIANGLE)
		vector_init(vec, sizeof(t_triangle));
	else if (type == SPHERE)
		vector_init(vec, sizeof(t_sphere));
	else if (type == PLANE)
		vector_init(vec, sizeof(t_plane));
	else
		vector_init(vec, sizeof(t_mesh));
}

static inline int	add_object(t_vector *vec, t_object *obj)
{
	if (vector_add(vec, &obj->mem, 1) == -1)
		return (-1);
	if (obj->type == TRIANGLE)
		((t_triangle *) get_last_vector_value(vec))->mat = obj->mat_id;
	else if (obj->type == SPHERE)
		((t_sphere *) get_last_vector_value(vec))->mat = obj->mat_id;
	else if (obj->type == PLANE)
		((t_plane *) get_last_vector_value(vec))->mat = obj->mat_id;
	return (0);
}

static inline int	fill_mem(
	t_opencl *state, cl_mem *dest, t_vector *vec, t_object_type type)
{
	size_t		i;
	int			err;
	t_object	*obj;
	t_vector	temp;

	init_vec_type(&temp, type);
	obj = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		if (obj[i].type == type)
		{
			if (add_object(&temp, &obj[i]) == -1)
				return (-1);
		}
		++i;
	}
	*dest = clCreateBuffer(state->context, CL_MEM_READ_ONLY
			| CL_MEM_COPY_HOST_PTR, temp.element_size * temp.num_elements,
			temp.data, &err);
	free_vector(&temp);
	return (err);
}

int	fill_object_mem(t_opencl *state, t_scene *scene)
{
	if (fill_mem(state, &scene->spheres, &scene->objects, SPHERE) == -1)
		return (-1);
	if (fill_mem(state, &scene->triangles, &scene->objects, TRIANGLE) == -1)
		return (-1);
	if (fill_mem(state, &scene->planes, &scene->objects, PLANE) == -1)
		return (-1);
	return (0);
}
