/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_aabb_surface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 03:12:00 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 19:55:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_aabb_surface(const t_bvh_aabb aabb)
{
	return (2.f * vec3_pairwise(vec3_max(vec3_sub(aabb.max, aabb.min),
				vec3_zero())));
}
