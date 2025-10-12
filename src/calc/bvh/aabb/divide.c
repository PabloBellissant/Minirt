/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:39:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 06:39:31 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bvh.h"
#include "calc.h"

void	quick_sort(void *array, size_t elem_count, size_t elem_size,
			int (*compare_function)(const void *, const void *));
int		(*get_axis_function(int axis))(const void *, const void *);

int	divide_half_left(t_vector *new_ptr, t_vector *old_ptr, t_aabb_bvh *bvh)
{
	int	cut_index;

	vector_init(new_ptr, sizeof(t_object *));
	new_ptr->num_elements = 0;
	cut_index = get_cut_index(old_ptr, bvh, get_cut_axis(bvh));
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

int	subdivide(t_aabb_bvh *bvh, t_vector *bvh_vec, t_vector *obj_vec)
{
	t_aabb_bvh	temp;
	t_vector	new_object_ptr;
	int			temp_depth;
	int			axis;

	set_size(bvh, obj_vec);
	if (obj_vec->num_elements > 1)
	{
		axis = get_cut_axis(bvh);
		quick_sort(obj_vec->data, obj_vec->num_elements - 1,
			sizeof(t_object *), get_axis_function(axis));
		vector_add(bvh_vec, &temp, 1);
		bvh->next_a = get_last_vector_value(bvh_vec);
		divide_half_left(&new_object_ptr, obj_vec, bvh);
		bvh->depth = subdivide(bvh->next_a, bvh_vec, &new_object_ptr);
		vector_add(bvh_vec, &temp, 1);
		bvh->next_b = get_last_vector_value(bvh_vec);
		divide_half_right(&new_object_ptr, obj_vec);
		temp_depth = subdivide(bvh->next_b, bvh_vec, &new_object_ptr);
		bvh->depth = imax(temp_depth, bvh->depth) + 1;
		return (bvh->depth);
	}
	bvh->object_a = *(t_object **)obj_vec->data;
	bvh->depth = 0;
	return (0);
}
