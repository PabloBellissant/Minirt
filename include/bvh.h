/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:56:25 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 16:32:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H
#include "parsing.h"
# include "vectors.h"
# include "libft.h"
# include <float.h>

typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_ray		t_ray;

typedef struct s_cuboid
{
	cl_float3	min;
	cl_float3	max;
}	t_cuboid;

typedef enum e_bvh_ary_type
{
	BVH2 = 0,
	BVH4,
	BVH8
}	t_bvh_ary_type;

typedef struct s_aabb_bvh
{
	union
	{
		struct
		{
			cl_float3	min;
			cl_float3	max;
		};
		t_cuboid	cuboid;
	};
	union
	{
		int	next;
		int	object;
		int	children[8];
	};
	int			depth;
	int			skip;
	int			child_count;
	t_bvh_ary_type	bvh_ary_type;
}	t_aabb_bvh;

typedef struct s_sphere_bvh	t_sphere_bvh;
typedef struct s_sphere_bvh
{
	int			depth;
	struct
	{
		t_vec3	pos;
		float	size;
	};
	union
	{
		struct
		{
			t_sphere_bvh	*next_a;
			t_sphere_bvh	*next_b;
		};
		t_object	*object;
	};
}	t_sphere_bvh;

typedef struct s_opencl		t_opencl;
typedef enum e_object_type	t_object_type;

int				get_object(t_vector *obj_vec);
int				create_aabb_bvh(t_scene *scene);
float			get_cuboid_area(t_cuboid *cuboid);
float			get_next_bvh_area(t_aabb_bvh *a, t_aabb_bvh *b);
void			merge_bvh(t_vector *bvh_vec, size_t a_index, size_t b_index);
void			merge_nearest_bvh(t_vector *bvh_vec, int *parents);
int				hit_aabb_bvh(t_ray *ray, t_aabb_bvh *bvh, int bvh_index, t_object *objects);
size_t			get_bvh_count(t_vector *objects, t_object_type type);
t_aabb_bvh		*get_aabb_root(t_vector *bvh_vec, int *parents);
bool			is_bvh_full(t_vector *bvh_vec, int *parents);
int 			create_aabb_bvh_sah(t_scene *scene);
int				create_sphere_bvh(t_scene *scene);
void			merge_nearest_sphere_bvh(t_vector *bvh_vec, int *parents);
float			get_next_sphere_bvh_area(t_sphere_bvh *a, t_sphere_bvh *b);
void			merge_sphere_bvh(t_vector *bvh_vec, size_t a_index,
					size_t b_index);
t_sphere_bvh	*get_sphere_root(t_vector *bvh_vec, int *parents);
int				load_bvh(int mode, t_scene *scene, t_opencl *state);
void			get_min_max(t_object *o, t_vec3 *min, t_vec3 *max);
void			set_size(t_aabb_bvh *bvh, t_vector *index_vec, t_object *objects);
int				get_cut_index(t_vector *object_ptr, t_aabb_bvh *bvh, int axis);
int				get_cut_axis(t_aabb_bvh *parent);
int				subdivide(
		int index, t_vector *bvh_vec,
		t_vector *obj_vec, t_object *objects);
t_vec3			get_center(const t_object *o);

int			create_bvh4_from_bvh2(const t_aabb_bvh *bvh2, int bvh2_size,
				t_aabb_bvh *out_bvh4, int out_capacity, int *out_size);
int			create_bvh8_from_bvh2(const t_aabb_bvh *bvh2, int bvh2_size,
				t_aabb_bvh *out_bvh8, int out_capacity, int *out_size);
void		free_bvh_structures(t_scene *scene);

#endif

// 20000
