/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_subdivide.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:13:52 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 15:20:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"

int	sah_subdivide(int index, t_vector *bvh_vec, t_vector *index_vec, t_object *objects)
{
    t_aabb_bvh	*bvh;
    t_aabb_bvh	temp;

    t_vector	left_objs;
    t_vector	right_objs;

    int temp_depth;

    int	sah_axis = -1;
    int	sah_bin = -1;

    t_vec3	cmin;
    t_vec3	cmax;

    float	extent;
    float	inv_extent;

    bvh = get_vector_value(bvh_vec, index);
    set_size(bvh, index_vec, objects);

    // Leaf condition
    if (index_vec->num_elements <= LEAF_SIZE)
    {
        bvh->depth = 0;
        bvh->object = get_object(index_vec);
        return (0);
    }

    // Try SAH split
    if (!choose_sah_split(index_vec, bvh, objects, &sah_axis, &sah_bin))
    {
        // No good SAH split found, make leaf
        bvh->depth = 0;
        bvh->object = get_object(index_vec);
        return (0);
    }

    // Get centroid bounds for partition
    get_sah_centroid_bounds(index_vec, objects, &cmin, &cmax);
    extent = (&cmax.x)[sah_axis] - (&cmin.x)[sah_axis];
    if (extent <= 0.0f)
    {
        // Degenerate, make leaf
        bvh->depth = 0;
        bvh->object = get_object(index_vec);
        return (0);
    }
    inv_extent = (float)NUM_BINS / extent;

    // Partition by bin
    partition_by_bin(&left_objs, &right_objs, index_vec, sah_axis, sah_bin,
                     cmin, inv_extent, objects);

    // Check for empty split
    if (left_objs.num_elements == 0 || right_objs.num_elements == 0)
    {
        free_vector(&left_objs);
        free_vector(&right_objs);
        bvh->depth = 0;
        bvh->object = get_object(index_vec);
        return (0);
    }

    // Recurse on left
    ft_memset(&temp, 0, sizeof(temp));
    vector_add(bvh_vec, &temp, 1);
    bvh->depth = sah_subdivide(index + 1, bvh_vec, &left_objs, objects);

    // Recurse on right
    ft_memset(&temp, 0, sizeof(temp));
    vector_add(bvh_vec, &temp, 1);
    bvh->next = bvh_vec->num_elements - 1;
    temp_depth = sah_subdivide(bvh->next, bvh_vec, &right_objs, objects);

    bvh->depth = max(temp_depth, bvh->depth) + 1;

    free_vector(&left_objs);
    free_vector(&right_objs);

    return (bvh->depth);
}
