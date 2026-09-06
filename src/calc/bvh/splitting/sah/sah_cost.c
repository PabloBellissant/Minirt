/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_cost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 07:15:19 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:33:14 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_bounds_surface(const t_bvh_header *bvh_header,
			const t_bvh_bounds bounds);

float	sah_cost(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_sah_bucket sums[BVH_LR])
{
	const float	sa_p = get_bounds_surface(bvh_header, parent_bounds);
	float		sa[BVH_LR];

	if (sa_p <= 0.f)
		return (SAH_SM);
	sa[BVH_L] = get_bounds_surface(bvh_header, sums[BVH_L].bounds);
	sa[BVH_R] = get_bounds_surface(bvh_header, sums[BVH_R].bounds);
	return (SAH_CT + SAH_CI * ((sa[BVH_L] / sa_p) * (float)sums[BVH_L].count
			+ (sa[BVH_R] / sa_p) * (float)sums[BVH_R].count));
}
