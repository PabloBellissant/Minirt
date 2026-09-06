/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bounds_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 03:10:04 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 20:19:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_sphere_surface(const t_bvh_sphere sphere);
float	get_aabb_surface(const t_bvh_aabb aabb);
float	get_obb_surface(const t_bvh_obb obb);

float	get_bounds_surface(const t_bvh_header *bvh_header,
		const t_bvh_bounds bounds)
{
	if (bvh_header->shape == BVH_SPHERE)
		return (get_sphere_surface(bounds.sphere));
	else if (bvh_header->shape == BVH_AABB)
		return (get_aabb_surface(bounds.aabb));
	else if (bvh_header->shape == BVH_OBB)
		return (get_obb_surface(bounds.obb));
	return (0.0f);
}
