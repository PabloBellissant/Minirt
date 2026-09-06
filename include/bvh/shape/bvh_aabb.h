/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_aabb.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:19:12 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/25 01:37:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_AABB_H
# define BVH_AABB_H

typedef struct s_cuboid
{
	t_vec3	min;
	t_vec3	max;
}			t_cuboid;//bvh_common.h ?

typedef struct s_bvh_aabb
{
	union
	{
		struct
		{
			t_vec3	min;
			t_vec3	max;
		};
		t_cuboid	cuboid;
	};
}					t_bvh_aabb;

#endif//BVH_AABB_H
