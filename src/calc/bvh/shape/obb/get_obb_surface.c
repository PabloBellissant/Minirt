/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obb_surface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 03:11:38 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:28:05 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_obb_surface(const t_bvh_obb obb)
{
	return (2.f * vec3_pairwise(vec3_max(vec3_scale(obb.half_extents, 2.f),
				vec3_zero())));
}
