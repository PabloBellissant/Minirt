/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_union.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:22:09 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 02:22:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cuboid_union(t_cuboid *a, const t_cuboid b)
{
	a->min = vec3_min(a->min, b.min);
	a->max = vec3_max(a->max, b.max);
}

void	cuboid_point_union(t_cuboid *a, const t_vec3 v)
{
	a->min = vec3_min(a->min, v);
	a->max = vec3_max(a->max, v);
}

void	cuboid_sphere_union(t_cuboid *a, const t_vec3 c, const float r)
{
	cuboid_point_union(a, vec3_sub(c, vec3_set(r)));
	cuboid_point_union(a, vec3_add(c, vec3_set(r)));
}
