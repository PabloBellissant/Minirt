/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:39:29 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/19 15:07:05 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "bvh.h"

int		imax(int a, int b);
void	quick_sort(void *array, size_t elem_count, size_t elem_size,
			int (*compare_function)(const void *, const void *));
int		(*get_axis_function(int axis))(const void *, const void *);

int	divide_half_left(t_vector *new_ptr, t_vector *old_ptr, int cut_index)
{
	vector_init(new_ptr, sizeof(t_vec2i));
	new_ptr->num_elements = 0;
	return (vector_add(new_ptr, old_ptr->data, (size_t)cut_index));
}

int	divide_half_right(t_vector *new_ptr, t_vector *old_ptr)
{
	size_t	cut_index;
	void	*src;

	cut_index = old_ptr->num_elements - new_ptr->num_elements;
	src = (char *)old_ptr->data + old_ptr->element_size * new_ptr->num_elements;
	new_ptr->num_elements = 0;
	return (vector_add(new_ptr, src, cut_index));
}

int semi_sort_x(t_vec2i *index, int input_size, t_object *objects)
{
	int i;
	int j;
	int pivot;
	t_vec2i tmp;

	if (input_size < 2)
		return (0);
	pivot = index[input_size / 2].x;
	i = 0;
	j = input_size - 1;
	while (i <= j)
	{
		while (get_center(&objects[index[i].x]).x < get_center(&objects[pivot]).x)
			i++;
		while (get_center(&objects[index[j].x]).x > get_center(&objects[pivot]).x)
			j--;
		if (i <= j)
		{
			tmp = index[i];
			index[i] = index[j];
			index[j] = tmp;
			i++;
			j--;
		}
	}
	semi_sort_x(index, j + 1, objects);
	semi_sort_x(index + i, input_size - i, objects);
	return (0);
}


int semi_sort_y(t_vec2i *index, int input_size,  t_object *objects)
{
	int i;
	int j;
	int pivot;
	t_vec2i tmp;

	if (input_size < 2)
		return (0);
	pivot = index[input_size / 2].x;
	i = 0;
	j = input_size - 1;
	while (i <= j)
	{
		while (get_center(&objects[index[i].x]).y < get_center(&objects[pivot]).y)
			i++;
		while (get_center(&objects[index[j].x]).y > get_center(&objects[pivot]).y)
			j--;
		if (i <= j)
		{
			tmp = index[i];
			index[i] = index[j];
			index[j] = tmp;
			i++;
			j--;
		}
	}
	semi_sort_y(index, j + 1, objects);
	semi_sort_y(index + i, input_size - i, objects);
	return (0);
}


int semi_sort_z(t_vec2i *index, int input_size, t_object *objects)
{
	int i;
	int j;
	int pivot;
	t_vec2i tmp;

	if (input_size < 2)
		return (0);
	pivot = index[input_size / 2].x;
	i = 0;
	j = input_size - 1;
	while (i <= j)
	{
		while (get_center(&objects[index[i].x]).z < get_center(&objects[pivot]).z)
			i++;
		while (get_center(&objects[index[j].x]).z > get_center(&objects[pivot]).z)
			j--;
		if (i <= j)
		{
			tmp = index[i];
			index[i] = index[j];
			index[j] = tmp;
			i++;
			j--;
		}
	}
	semi_sort_z(index, j + 1, objects);
	semi_sort_z(index + i, input_size - i, objects);
	return (0);
}

float	get_mid(t_aabb_bvh *bvh, int axis)
{
	if (axis == 0)
		return (bvh->max.x + bvh->min.x / 2.0f);
	else if (axis == 1)
		return (bvh->max.y + bvh->min.y / 2.0f);
	return (bvh->max.z + bvh->min.z / 2.0f);
}

int semi_sort_(t_vector *index_vec, int axis, t_object *objects)
{
	t_vec2i	*index;
	int	input_size;

	index = index_vec->data;
	input_size = index_vec->num_elements;
	if (axis == 0)
		return (semi_sort_x(index, input_size, objects));
	else if (axis == 1)
		return (semi_sort_y(index, input_size, objects));
	return (semi_sort_z(index, input_size, objects));
}

int	subdivide(int index, t_vector *bvh_vec, t_vector *index_vec, t_object *objects)
{
	t_aabb_bvh	temp;
	t_vector	new_index_ptr;
	int			temp_depth;
	int			axis;
	t_aabb_bvh	*bvh;

	bvh = get_vector_value(bvh_vec, index);
	set_size(bvh, index_vec, objects);
	if (index_vec->num_elements > 1)
	{
		axis = get_cut_axis(bvh);
		semi_sort_(index_vec, axis, objects);
		int cut_index = index_vec->num_elements / 2.0f;
		vector_add(bvh_vec, &temp, 1);
		divide_half_left(&new_index_ptr, index_vec, cut_index);
		bvh->depth = subdivide(index + 1, bvh_vec, &new_index_ptr, objects);
		vector_add(bvh_vec, &temp, 1);
		bvh->next = bvh_vec->num_elements - 1;
		divide_half_right(&new_index_ptr, index_vec);
		temp_depth = subdivide(bvh->next, bvh_vec, &new_index_ptr, objects);
		bvh->depth = imax(temp_depth, bvh->depth) + 1;
		free_vector(&new_index_ptr);
		return (bvh->depth);
	}
	bvh->depth = 0;
	bvh->object = get_object(index_vec);
	return (0);
}
