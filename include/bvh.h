/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:56:25 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/06 09:18:37 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H
# include "vectors.h"
# include "libft.h"

typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_ray		t_ray;

typedef struct s_cuboid
{
	t_vec3	min;
	t_vec3	max;
}	t_cuboid;

typedef struct s_aabb_bvh	t_aabb_bvh;
typedef struct s_aabb_bvh
{
	int			depth;
	union
	{
		struct
		{
			t_vec3	min;
			t_vec3	max;
		};
		t_cuboid	cuboid;
	};
	union
	{
		struct
		{
			t_aabb_bvh	*next_a;
			t_aabb_bvh	*next_b;
		};
		struct
		{
			t_object	*object_a;
			t_object	*object_b;
		};
	};
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

int				create_aabb_bvh(t_scene *scene);
float			get_bvh_area(t_cuboid *cuboid);
float			get_next_bvh_area(t_aabb_bvh *a, t_aabb_bvh *b);
void			merge_bvh(t_vector *bvh_vec, size_t a_index, size_t b_index);
void			merge_nearest_bvh(t_vector *bvh_vec, int *parents);
t_object		*hit_aabb_bvh(t_ray *ray, t_aabb_bvh *bvh);
size_t			get_bvh_count(t_vector *objects);
t_aabb_bvh		*get_aabb_root(t_vector *bvh_vec, int *parents);
bool			is_bvh_full(t_vector *bvh_vec, int *parents);
int				create_sphere_bvh(t_scene *scene);
void			merge_nearest_sphere_bvh(t_vector *bvh_vec, int *parents);
float			get_next_sphere_bvh_area(t_sphere_bvh *a, t_sphere_bvh *b);
void			merge_sphere_bvh(t_vector *bvh_vec, size_t a_index,
					size_t b_index);
t_sphere_bvh	*get_sphere_root(t_vector *bvh_vec, int *parents);
int				load_bvh(int mode, t_scene *scene);
void			get_min_max(t_object *o, t_vec3 *min, t_vec3 *max);
void			set_size(t_aabb_bvh *bvh, t_vector *objects_vec);
int				get_cut_index(t_vector *object_ptr, t_aabb_bvh *bvh, int axis);
int				get_cut_axis(t_aabb_bvh *parent);
int				subdivide(t_aabb_bvh *bvh, t_vector *bvh_vec,
					t_vector *obj_vec);
t_vec3			get_center(const t_object *o);

#endif

// 20000
