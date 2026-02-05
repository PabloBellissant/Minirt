/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_partitionning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:01:21 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 14:58:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"
#include "object.h"

// Split index_vec into left/right by bin
void partition_by_bin(t_vector *left, t_vector *right,
                            t_vector *index_vec, int axis,
                            int split_bin, t_vec3 cmin, float inv_extent,
                            t_object *objects)
{
    size_t i;
    t_vec2i *indices;
    t_vec3 c;
    int b;
    t_vec2i idx;

    vector_init(left, sizeof(t_vec2i));
    vector_init(right, sizeof(t_vec2i));

    indices = (t_vec2i *)index_vec->data;
    i = 0;
    while (i < index_vec->num_elements)
    {
        idx = indices[i];
        c = get_bin_centroid(objects, idx.x);
        b = (int)(((&c.x)[axis] - (&cmin.x)[axis]) * inv_extent);
        if (b < 0)
            b = 0;
        if (b >= NUM_BINS)
            b = NUM_BINS - 1;

        if (b <= split_bin)
            vector_add(left, &idx, 1);
        else
            vector_add(right, &idx, 1);
        i++;
    }
}
