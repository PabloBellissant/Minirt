/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:00:09 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:18:11 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static const char	*get_shape_name(t_bvh_shape shape)
{
	if (shape == BVH_SPHERE)
		return ("SPHERE");
	else if (shape == BVH_AABB)
		return ("AABB");
	else if (shape == BVH_OBB)
		return ("OBB");
	return ("UNKNOWN");
}

static const char	*get_split_name(t_bvh_split split)
{
	if (split == MED_PRIM)
		return ("Median Primitive");
	else if (split == MED_SPACE)
		return ("Median Space");
	else if (split == SAH)
		return ("Surface Area Heuristic");
	return ("UNKNOWN");
}

static void	print_build_time(size_t build_time)
{
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM_HIGHLIGHT"%zu"
		C_RESET" "C_DIM"μs"C_RESET" "C_BRACKET"("C_NUM"%.2f"C_RESET" "
		C_DIM"ms"C_RESET" "C_DIM"/"C_RESET" "C_NUM"%.4f"C_RESET" "
		C_DIM"s"C_BRACKET")"C_RESET"\n\n", "Build time", build_time,
		build_time / 1000.0f, build_time / 1000000.0f);
}

void	print_bvh_config(t_bvh_header *h)
{
	printf(C_HEADER" ▎BVH Configuration                          "
		C_RESET"\n");
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM_HIGHLIGHT"%s"
		C_RESET"\n", "Shape", get_shape_name(h->shape));
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM_HIGHLIGHT"%s"
		C_RESET"\n", "Split algo", get_split_name(h->splitting_algo));
	printf(C_LABEL"  ▸ %-18s"C_SEPARATOR"│ "C_RESET C_NUM"%d"C_RESET"\n",
		"Arity", BVH_ARITY);
	print_build_time(h->build_time);
}
