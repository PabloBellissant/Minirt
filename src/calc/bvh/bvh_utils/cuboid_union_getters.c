/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_union_getters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:22:23 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 02:22:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cuboid	get_cuboid_union(const t_cuboid a, const t_cuboid b)
{
	return ((t_cuboid){.min = vec3_min(a.min, b.min),
		.max = vec3_max(a.max, b.max)});
}

t_cuboid	get_point_cuboid_union(const t_cuboid a, const t_vec3 p)
{
	return ((t_cuboid){.min = vec3_min(a.min, p), .max = vec3_max(a.max, p)});
}

t_cuboid	get_sphere_cuboid_union(const t_cuboid a, const t_vec3 c,
				const float r)
{
	const t_cuboid	neg = get_point_cuboid_union(a, vec3_sub(c, vec3_set(r)));
	const t_cuboid	pos = get_point_cuboid_union(a, vec3_add(c, vec3_set(r)));

	return (get_cuboid_union(pos, neg));
}
