/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:39:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/15 04:17:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bvh.h"
#include "calc.h"

void	quick_sort(void *array, size_t elem_count, size_t elem_size,
			int (*compare_function)(const void *, const void *));
int		(*get_axis_function(int axis))(const void *, const void *);

int	divide_half_left(t_vector *new_ptr, t_vector *old_ptr, int cut_index)
{
	vector_init(new_ptr, sizeof(t_object *));
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

t_object	*get_object(t_vector *obj_vec)
{
	if (obj_vec->max_elements != 0)
		return (*(t_object **)get_last_vector_value(obj_vec));
	return (NULL);
}

int semi_sort_(t_object **obj, int input_size, int axis, float middle_val)
{
	int			write_pos;
	int			read_pos;
	t_object	*temp;

	write_pos = 0;
	read_pos = 0;
	while (read_pos < input_size)
	{
		//dprintf(2, "middle : %f, searchimg : %f\n", middle_val, get_center(obj[read_pos]).data[axis]);
		if (get_center(obj[read_pos]).data[axis] < middle_val)
		{
			if (write_pos != read_pos)
			{
				temp = obj[write_pos];
				obj[write_pos] = obj[read_pos];
				obj[read_pos] = temp;
			}
			write_pos++;
		}
		++read_pos;
	}
	return (write_pos);
}

// void	semi_sort(void *array, size_t elem_count, size_t elem_size,
// 	int (*compare_function)(const void *, const void *));

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
		//quick_sort(obj_vec->data, obj_vec->num_elements - 1,
		// 	sizeof(t_object *), get_axis_function(axis));
		int cut_index = semi_sort_(obj_vec->data, obj_vec->num_elements - 1, axis, (bvh->max.data[axis] + bvh->min.data[axis]) / 2);
		cut_index = obj_vec->num_elements / 2;
		vector_add(bvh_vec, &temp, 1);
		bvh->next_a = get_last_vector_value(bvh_vec);
		divide_half_left(&new_object_ptr, obj_vec, cut_index);
		bvh->depth = subdivide(bvh->next_a, bvh_vec, &new_object_ptr);
		vector_add(bvh_vec, &temp, 1);
		bvh->next_b = get_last_vector_value(bvh_vec);
		divide_half_right(&new_object_ptr, obj_vec);
		temp_depth = subdivide(bvh->next_b, bvh_vec, &new_object_ptr);
		bvh->depth = imax(temp_depth, bvh->depth) + 1;
		free_vector(&new_object_ptr);
		return (bvh->depth);
	}
	bvh->depth = 0;
	bvh->object_a = get_object(obj_vec);
	return (0);
}
