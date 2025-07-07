/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:56:25 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/29 03:56:31 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "struct.h"

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
