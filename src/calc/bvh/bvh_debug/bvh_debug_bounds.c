/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:59:53 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:06:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static inline void	print_sphere_bounds(const t_bvh_bounds *b)
{
	printf(C_DIM"sphere"C_BRACKET"("C_RESET);
	printf(C_KEY"pos"C_RESET"="C_BRACKET"["C_NUM"%.2f"C_DIM","C_NUM"%.2f"
		C_DIM","C_NUM"%.2f"C_BRACKET"]"C_RESET" ", b->sphere.pos.x,
		b->sphere.pos.y, b->sphere.pos.z);
	printf(C_KEY"r"C_RESET"="C_NUM_HIGHLIGHT"%.2f"C_BRACKET")"C_RESET,
		b->sphere.radius);
}

static inline void	print_aabb_bounds(const t_bvh_bounds *b)
{
	printf(C_DIM"aabb"C_BRACKET"("C_RESET);
	printf(C_KEY"min"C_RESET"="C_BRACKET"["C_NUM"%.2f"C_DIM","C_NUM"%.2f"
		C_DIM","C_NUM"%.2f"C_BRACKET"]"C_RESET" ", b->aabb.min.x,
		b->aabb.min.y, b->aabb.min.z);
	printf(C_KEY"max"C_RESET"="C_BRACKET"["C_NUM"%.2f"C_DIM","C_NUM"%.2f"
		C_DIM","C_NUM"%.2f"C_BRACKET"]"C_BRACKET")"C_RESET,
		b->aabb.max.x, b->aabb.max.y, b->aabb.max.z);
}

static inline void	print_obb_quat(const t_bvh_bounds *b)
{
	printf(C_KEY"quat"C_RESET"="C_BRACKET"["C_NUM"%.3f"C_DIM","C_NUM"%.3f"
		C_DIM","C_NUM"%.3f"C_DIM","C_NUM"%.3f"C_BRACKET"]"C_BRACKET")"
		C_RESET, b->obb.q.x, b->obb.q.y, b->obb.q.z, b->obb.q.w);
}

static inline void	print_obb_bounds(const t_bvh_bounds *b)
{
	printf(C_DIM"obb"C_BRACKET"("C_RESET);
	printf(C_KEY"center"C_RESET"="C_BRACKET"["C_NUM"%.2f"C_DIM","C_NUM"%.2f"
		C_DIM","C_NUM"%.2f"C_BRACKET"]"C_RESET" ", b->obb.center.x,
		b->obb.center.y, b->obb.center.z);
	printf(C_KEY"extents"C_RESET"="C_BRACKET"["C_NUM"%.2f"C_DIM","C_NUM"%.2f"
		C_DIM","C_NUM"%.2f"C_BRACKET"]"C_RESET" ", b->obb.half_extents.x,
		b->obb.half_extents.y, b->obb.half_extents.z);
	print_obb_quat(b);
}

void	print_bounds(const t_bvh_bounds *b, const t_bvh_shape shape)
{
	if (shape == BVH_SPHERE)
		print_sphere_bounds(b);
	else if (shape == BVH_AABB)
		print_aabb_bounds(b);
	else if (shape == BVH_OBB)
		print_obb_bounds(b);
}
