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
#include <float.h>
#include "bvh.h"
#include "render.h"

static void	update_min_max(t_object *o, t_vec3 *min, t_vec3 *max);

static t_vec3	get_center(t_object *o)
{
	//t_vec3	temp;
	t_vec3	min;

	if (o->type == SPHERE)
	{
		min.x = o->sphere.pos.x;
		min.y = o->sphere.pos.y;
		min.z = o->sphere.pos.z;
	}
	if (o->type == TRIANGLE)
	{
		min.x = (o->triangle.p0.pos.x + o->triangle.p1.pos.x + o->triangle.p2.pos.x) / 3.0f;
		min.y = (o->triangle.p0.pos.y + o->triangle.p1.pos.y + o->triangle.p2.pos.y) / 3.0f;
		min.z = (o->triangle.p0.pos.z + o->triangle.p1.pos.z + o->triangle.p2.pos.z) / 3.0f;
	}
	if (o->type == CYLINDER)
	{
		// t_vec3 P2 = vec3_add(o->cylinder.pos, vec3_scale(o->cylinder.rot, o->cylinder.height));
		//
		// temp.x = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.x * o->cylinder.rot.x);
		// temp.y = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.y * o->cylinder.rot.y);
		// temp.z = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.z * o->cylinder.rot.z);
		//
		// min.x = fminf(o->cylinder.pos.x - temp.x, P2.x - temp.x);
		// min.y = fminf(o->cylinder.pos.y - temp.y, P2.y - temp.y);
		// min.z = fminf(o->cylinder.pos.z - temp.z, P2.z - temp.z);
	}
	return (min);
}

void	set_size(t_aabb_bvh *bvh, t_vector *objects_vec)
{
	size_t		i;
	t_object	**objects;
	t_vec3		temp_min;
	t_vec3		temp_max;

	bvh->min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	bvh->max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	objects = objects_vec->data;
	i = 0;
	while (i < objects_vec->num_elements)
	{
		if (objects[i]->type != PLANE && objects[i]->type != LIGHT)
		{
			update_min_max(objects[i], &temp_min, &temp_max);
			bvh->min.x = fminf(bvh->min.x, temp_min.x);
			bvh->min.y = fminf(bvh->min.y, temp_min.y);
			bvh->min.z = fminf(bvh->min.z, temp_min.z);
			bvh->max.x = fmaxf(bvh->max.x, temp_max.x);
			bvh->max.y = fmaxf(bvh->max.y, temp_max.y);
			bvh->max.z = fmaxf(bvh->max.z, temp_max.z);
		}
		++i;
	}
}

int get_cut_axis(t_aabb_bvh *parent)
{
	t_vec3 distance;

	distance.x = parent->max.x - parent->min.x;
	distance.y = parent->max.y - parent->min.y;
	distance.z = parent->max.z - parent->min.z;

	if (distance.x >= distance.y && distance.x >= distance.z)
		return (0);
	if (distance.y >= distance.z)
		return (1);
	return (2);
}

int	sort_object_ptr(t_vector *vec, int axis)
{
	size_t i;
	size_t j;
	t_object **object;
	t_object *temp_ptr;

	object = vec->data;
	i = 0;
	while (i < vec->num_elements - 1)
	{
		j = 0;
		while (j < vec->num_elements - 1 - i)
		{
			if (get_center(object[j]).data[axis] > get_center(object[j + 1]).data[axis])
			{
				temp_ptr = object[j];
				object[j] = object[j + 1];
				object[j + 1] = temp_ptr;
			}
			++j;
		}
		++i;
	}
	return (0);
}


static int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

# define QUALIBRATION 1

int	get_cut_index(t_vector *object_ptr, t_aabb_bvh *bvh)
{
	float		middle_value;
	float		actual_value;
	int			axis;
	int			i;
	int			end;
	t_object	**object;

	axis = get_cut_axis(bvh);
	object = (t_object **)object_ptr->data;
	middle_value = (bvh->max.data[axis] + bvh->min.data[axis]) / 2;
	i = imax(0, (int)(object_ptr->num_elements / 2) - QUALIBRATION);
	end = imin((int)(object_ptr->num_elements / 2) + QUALIBRATION, (int)object_ptr->num_elements);
	while (i < end)
	{
		actual_value = get_center(object[i]).data[axis];
		if (actual_value >= middle_value)
			break;
		++i;
	}
	if (i == 0)
		i = 1;
	else if (i == (int)object_ptr->num_elements)
		i = (int)object_ptr->num_elements - 1;
	return (i);
}

int	divide_half_left(t_vector *new_ptr, t_vector *old_ptr, t_aabb_bvh *bvh)
{
	int	cut_index;

	new_ptr->num_elements = 0;
	dprintf(2, "%zu\n", old_ptr->num_elements);
	(void) bvh;
	cut_index = get_cut_index(old_ptr, bvh);
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

int	subdivise(t_aabb_bvh *bvh, t_vector *bvh_vec, t_vector *objects_vec)
{
	t_aabb_bvh	temp;
	t_vector	new_object_ptr;
	int			temp_depth;

	ft_bzero(bvh, sizeof(t_aabb_bvh));
	vector_init(&new_object_ptr, sizeof(t_object *));
	set_size(bvh, objects_vec);
	if (objects_vec->num_elements > 1)
	{
		int	cut_axis = get_cut_axis(bvh);
		sort_object_ptr(objects_vec, cut_axis);
		vector_add(bvh_vec, &temp, 1);
		bvh->next_a = get_last_vector_value(bvh_vec);
		divide_half_left(&new_object_ptr, objects_vec, bvh);
		bvh->depth = subdivise(bvh->next_a, bvh_vec, &new_object_ptr);
		vector_add(bvh_vec, &temp, 1);
		bvh->next_b = get_last_vector_value(bvh_vec);
		divide_half_right(&new_object_ptr, objects_vec);
		temp_depth = subdivise(bvh->next_b, bvh_vec, &new_object_ptr);
		bvh->depth = imax(temp_depth, bvh->depth) + 1;
		return (bvh->depth);
	}
	bvh->object_a = *(t_object **)objects_vec->data;
	bvh->depth = 0;
	return (0);
}

int	create_root_bvh(t_vector *bvh, t_vector *objects)
{
	t_aabb_bvh	root_bvh;

	ft_bzero(&root_bvh, sizeof(t_aabb_bvh));
	root_bvh.min = (t_vec3) {{FLT_MAX, FLT_MAX, FLT_MAX}};
	root_bvh.max = (t_vec3) {{-FLT_MAX, -FLT_MAX, -FLT_MAX}};
	set_size(&root_bvh, objects);
	vector_add(bvh, &root_bvh, 1);
	return (0);
}

static void	update_min_max(t_object *o, t_vec3 *min, t_vec3 *max)
{
	t_vec3	temp;

	if (o->type == SPHERE)
	{
		min->x = o->sphere.pos.x - (o->sphere.diameter / 2);
		min->y = o->sphere.pos.y - (o->sphere.diameter / 2);
		min->z = o->sphere.pos.z - (o->sphere.diameter / 2);
		max->x = min->x + o->sphere.diameter;
		max->y = min->y + o->sphere.diameter;
		max->z = min->z + o->sphere.diameter;
	}
	if (o->type == TRIANGLE)
	{
		min->x = fminf(fminf(o->triangle.p0.pos.x, o->triangle.p1.pos.x), o->triangle.p2.pos.x);
		min->y = fminf(fminf(o->triangle.p0.pos.y, o->triangle.p1.pos.y), o->triangle.p2.pos.y);
		min->z = fminf(fminf(o->triangle.p0.pos.z, o->triangle.p1.pos.z), o->triangle.p2.pos.z);
		max->x = fmaxf(fmaxf(o->triangle.p0.pos.x, o->triangle.p1.pos.x), o->triangle.p2.pos.x);
		max->y = fmaxf(fmaxf(o->triangle.p0.pos.y, o->triangle.p1.pos.y), o->triangle.p2.pos.y);
		max->z = fmaxf(fmaxf(o->triangle.p0.pos.z, o->triangle.p1.pos.z), o->triangle.p2.pos.z);
	}
	if (o->type == CYLINDER)
	{
		t_vec3 P2 = vec3_add(o->cylinder.pos, vec3_scale(o->cylinder.rot, o->cylinder.height));

		temp.x = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.x * o->cylinder.rot.x);
		temp.y = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.y * o->cylinder.rot.y);
		temp.z = o->cylinder.radius * sqrtf(1.0f - o->cylinder.rot.z * o->cylinder.rot.z);

		min->x = fminf(o->cylinder.pos.x - temp.x, P2.x - temp.x);
		max->x = fmaxf(o->cylinder.pos.x + temp.x, P2.x + temp.x);
		min->y = fminf(o->cylinder.pos.y - temp.y, P2.y - temp.y);
		max->y = fmaxf(o->cylinder.pos.y + temp.y, P2.y + temp.y);
		min->z = fminf(o->cylinder.pos.z - temp.z, P2.z - temp.z);
		max->z = fmaxf(o->cylinder.pos.z + temp.z, P2.z + temp.z);
	}
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
		if (vector_add(pointer_vec, &actual, 1) == -1)
			return (-1);
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
	subdivise(get_last_vector_value(&bvh_vec), &bvh_vec, &objects_pointer);
	scene->bvh.aabb_bvh = bvh_vec.data;
	cut_bvh_leaf(scene->bvh.aabb_bvh);
	return (0);
}
