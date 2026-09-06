/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_bounds.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:53:14 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/03 00:28:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_BOUNDS_H
# define BVH_BOUNDS_H

# include "bvh_sphere.h"
# include "bvh_aabb.h"
# include "bvh_obb.h"

typedef union u_bvh_bounds
{
	t_bvh_sphere		sphere;
	t_bvh_aabb			aabb;
	t_bvh_obb			obb;
}						t_bvh_bounds;

#endif//BVH_BOUNDS_H
