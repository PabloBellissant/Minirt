/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sphere.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:18:34 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/26 23:22:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_SPHERE_H
# define BVH_SPHERE_H

typedef struct s_bvh_sphere
{
	union
	{
		t_vec3	pos;
		t_vec3	centroid;
	};
	union
	{
		float	r;
		float	radius;
	};
}				t_bvh_sphere;

#endif//BVH_SPHERE_H
