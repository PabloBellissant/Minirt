/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sah.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:57:11 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 15:53:51 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_SAH_H
# define BVH_SAH_H

# include "bvh.h"

# define NUM_BINS 16
# define LEAF_SIZE 1
# define CT 1.0f
# define CI 2.0f

# define SM 1e30f // give better name

#define LEFT 0
#define RIGHT 1
#define SPLIT 2

#define MMIN 0
#define MMAX 1
#define MM 2

typedef struct s_bin
{
	int		count;
	t_vec3	min;
	t_vec3	max;
}			t_bin;

t_vec3 get_bin_centroid(t_object *objects, int obj_idx);
void eval_min_max(t_vec3 *out[MM], t_vec3 a[MM], t_vec3 b[MM]);
void get_sah_centroid_bounds(t_vector *index_vec, t_object *objects,
                            t_vec3 *min, t_vec3 *max);

// Binning & splitting
void fill_bins(int axis, t_vec3 cmin, float inv_extent, 
              t_vector *index_vec, t_object *objects, t_bin bins[NUM_BINS]);
void partition_by_bin(t_vector *left, t_vector *right, 
                     t_vector *index_vec, int axis, int split_bin,
                     t_vec3 cmin, float inv_extent, t_object *objects);

void	get_axis_and_bin(int axis, int *out_axis, int *out_bin, t_bin bins[NUM_BINS], t_aabb_bvh *parent_bvh, float *best_cost);
// SAH selection
int choose_sah_split(t_vector *index_vec, t_aabb_bvh *parent_bvh,
                    t_object *objects, int *out_axis, int *out_bin);

// Build
int sah_subdivide(int index, t_vector *bvh_vec, 
                 t_vector *index_vec, t_object *objects);

#endif//BVH_SAH_H
