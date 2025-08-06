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

typedef struct s_scene	t_scene;
typedef struct s_object	t_object;
typedef struct s_ray	t_ray;
typedef struct s_hit_box_bvh
{
	float	ray_origin;
	float	ray_dir;
	float	box_min;
	float	box_max;
	float	t_min;
	float	t_max;
}	t_hit_box_bvh;

typedef struct s_bvh	t_bvh;
typedef struct s_bvh
{
	t_vec3	pos;
	t_vec3	size;
	int		depth;
	union
	{
		struct
		{
			t_bvh	*next_a;
			t_bvh	*next_b;
		};
		t_object	*object;
	};
	t_bvh	*parent;
}	t_bvh;

int			create_bvh(t_scene *scene);
float		get_bvh_area(t_bvh *bvh);
float		get_next_bvh_area(t_bvh *a, t_bvh *b);
int			merge_bvh(t_vector *bvh_vec, t_bvh *a, t_bvh *b);
int			merge_nearest_bvh(t_vector *bvh_vec);
t_object	*hit_bvh(t_ray *ray, t_bvh *bvh);

#endif
