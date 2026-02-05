/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:26:58 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 17:04:55 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <float.h>
#include "bvh.h"
#include "render.h"
#include "bvh_sah.h"

static int	create_root_bvh(t_vector *bvh, t_vector *index_vec, t_object *object_list);
static int	fill_pointer(t_vector *object_vec, t_vector *pointer_vec, t_object_type type);

static void set_skip_value(t_aabb_bvh *bvh, int id)
{
    int next_a;
	int	next_b;

	if (bvh[id].depth < 1)
		return ;
	next_a = id + 1;
    next_b = bvh[id].next;
    if (next_a != -1)
    {
        if (next_b != -1)
            bvh[next_a].skip = next_b;
        else
            bvh[next_a].skip = bvh[id].skip;
        set_skip_value(bvh, next_a);
    }
    if (next_b != -1)
    {
        bvh[next_b].skip = bvh[id].skip;
        set_skip_value(bvh, next_b);
    }
}

int	create_aabb_bvh(t_scene *scene)
{
	size_t		volume_count;
	t_vector	objects_pointer;
	
	t_vector	bvh_vec;
	volume_count = get_bvh_count(&scene->objects, SPHERE);
	vector_init(&bvh_vec, sizeof(t_aabb_bvh));
	if (set_vector_size(&bvh_vec, volume_count) != 0)
		return (-1);
	if (fill_pointer(&scene->objects, &objects_pointer, SPHERE) != 0)
	{
		free_vector(&bvh_vec);
		return (-1);
	}
	create_root_bvh(&bvh_vec, &objects_pointer, scene->objects.data);
	subdivide(bvh_vec.num_elements - 1, &bvh_vec, &objects_pointer, scene->objects.data);
	free_vector(&objects_pointer);
	scene->bvh.sphere_bvh = bvh_vec.data;
	set_skip_value(scene->bvh.sphere_bvh, 0);
	scene->bvh.sphere_bvh_size = bvh_vec.num_elements;

	t_vector	triangle_bvh_vec;
	volume_count = get_bvh_count(&scene->objects, TRIANGLE);
	vector_init(&triangle_bvh_vec, sizeof(t_aabb_bvh));
	if (set_vector_size(&triangle_bvh_vec, volume_count) != 0)
		return (-1);
	if (fill_pointer(&scene->objects, &objects_pointer, TRIANGLE) != 0)
	{
		free_vector(&triangle_bvh_vec);
		return (-1);
	}
	create_root_bvh(&triangle_bvh_vec, &objects_pointer, scene->objects.data);
	subdivide(triangle_bvh_vec.num_elements - 1, &triangle_bvh_vec, &objects_pointer, scene->objects.data);
	free_vector(&objects_pointer);
	scene->bvh.triangle_bvh = triangle_bvh_vec.data;
	set_skip_value(scene->bvh.triangle_bvh, 0);
	scene->bvh.triangle_bvh_size = triangle_bvh_vec.num_elements;
	return (0);
}

int create_aabb_bvh_sah(t_scene *scene)
{
    size_t   volume_count;
    t_vector objects_pointer;
    t_vector bvh_vec;
    t_vector triangle_bvh_vec;

    /* -------- Sphere BVH -------- */
    volume_count = get_bvh_count(&scene->objects, SPHERE);
    vector_init(&bvh_vec, sizeof(t_aabb_bvh));
    if (set_vector_size(&bvh_vec, volume_count) != 0)
        return (-1);
    if (fill_pointer(&scene->objects, &objects_pointer, SPHERE) != 0)
    {
        free_vector(&bvh_vec);
        return (-1);
    }
    create_root_bvh(&bvh_vec, &objects_pointer, scene->objects.data);
    /* SAH-based subdivision instead of subdivide() */
    sah_subdivide(bvh_vec.num_elements - 1, &bvh_vec,
                  &objects_pointer, scene->objects.data);
    free_vector(&objects_pointer);
	scene->bvh.sphere_bvh = bvh_vec.data;
	set_skip_value(scene->bvh.sphere_bvh, 0);
	scene->bvh.sphere_bvh_size = bvh_vec.num_elements;
    /*
    scene->bvh_sphere_sah = bvh_vec.data;
    set_skip_value(scene->bvh_sphere_sah, 0);
    scene->bvh_sphere_sah_size = bvh_vec.num_elements;
    */

    /* -------- Triangle BVH -------- */
    volume_count = get_bvh_count(&scene->objects, TRIANGLE);
    vector_init(&triangle_bvh_vec, sizeof(t_aabb_bvh));
    if (set_vector_size(&triangle_bvh_vec, volume_count) != 0)
        return (-1);
    if (fill_pointer(&scene->objects, &objects_pointer, TRIANGLE) != 0)
    {
        free_vector(&triangle_bvh_vec);
        return (-1);
    }
    create_root_bvh(&triangle_bvh_vec, &objects_pointer, scene->objects.data);
    /* SAH-based subdivision instead of subdivide() */
    sah_subdivide(triangle_bvh_vec.num_elements - 1, &triangle_bvh_vec,
                  &objects_pointer, scene->objects.data);
    free_vector(&objects_pointer);
	scene->bvh.triangle_bvh = triangle_bvh_vec.data;
	set_skip_value(scene->bvh.triangle_bvh, 0);
	scene->bvh.triangle_bvh_size = triangle_bvh_vec.num_elements;

	scene->bvh.triangle_bvh4 = (t_aabb_bvh *)malloc(
		sizeof(t_aabb_bvh) * scene->bvh.triangle_bvh_size);
	if (!scene->bvh.triangle_bvh4)
		return (-1);
	if (create_bvh4_from_bvh2(scene->bvh.triangle_bvh,
			scene->bvh.triangle_bvh_size,
			scene->bvh.triangle_bvh4,
			scene->bvh.triangle_bvh_size,
			&scene->bvh.triangle_bvh4_size) != 0)
	{
		free(scene->bvh.triangle_bvh4);
		return (-1);
	}

	/* Build BVH4 from SAH BVH2 (spheres) */
	scene->bvh.sphere_bvh4 = (t_aabb_bvh *)malloc(
		sizeof(t_aabb_bvh) * scene->bvh.sphere_bvh_size);
	if (!scene->bvh.sphere_bvh4)
	{
		free(scene->bvh.triangle_bvh4);
		return (-1);
	}
	if (create_bvh4_from_bvh2(scene->bvh.sphere_bvh,
			scene->bvh.sphere_bvh_size,
			scene->bvh.sphere_bvh4,
			scene->bvh.sphere_bvh_size,
			&scene->bvh.sphere_bvh4_size) != 0)
	{
		free(scene->bvh.triangle_bvh4);
		free(scene->bvh.sphere_bvh4);
		return (-1);
	}


    return (0);
}

static int	create_root_bvh(t_vector *bvh, t_vector *index_vec, t_object *object_list)
{
	t_aabb_bvh	root_bvh;

	ft_bzero(&root_bvh, sizeof(t_aabb_bvh));
	root_bvh.skip = -1;
	if (index_vec->num_elements != 0)
	{
		root_bvh.min = vec3(FLT_MAX, FLT_MAX, FLT_MAX); 
		root_bvh.max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		set_size(&root_bvh, index_vec, object_list);
	}
	else
	{
		root_bvh.min = vec3(0, 0, 0);
		root_bvh.max = vec3(0, 0, 0);
	}
	vector_add(bvh, &root_bvh, 1);
	return (0);
}

static int	fill_pointer(t_vector *object_vec, t_vector *pointer_vec, t_object_type type)
{
	t_vec2i		i;
	t_object	*object;

	vector_init(pointer_vec, sizeof(t_vec2i));
	object = object_vec->data;
	i.x = 0;
	i.y = 0;
	while (i.x < (int) object_vec->num_elements)
	{
		if (object[i.x].type == type)
		{
			if (vector_add(pointer_vec, &i, 1) == -1)
				return (-1);
			++i.y;
		}
		++i.x;
	}
	return (0);
}
