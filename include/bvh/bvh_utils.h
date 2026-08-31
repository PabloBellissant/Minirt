/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:17:18 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 02:23:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_UTILS_H
# define BVH_UTILS_H

# include "vectors.h"
# include "bvh_shape.h"

t_cuboid	cuboid(const t_vec3 min, const t_vec3 max);
t_cuboid	cuboid_zero(void);
t_cuboid	cuboid_inf(void);

t_cuboid	get_cuboid_union(const t_cuboid a, const t_cuboid b);
t_cuboid	get_point_cuboid_union(const t_cuboid a, const t_vec3 b);
t_cuboid	get_sphere_cuboid_union(const t_cuboid a, const t_vec3 c,
				const float r);

t_vec3		get_cuboid_extent(const t_cuboid cuboid);
t_vec3		cuboid_center(const t_cuboid c);
t_vec3		cuboid_half(const t_cuboid c);

void		cuboid_union(t_cuboid *a, const t_cuboid b);
void		cuboid_point_union(t_cuboid *a, const t_vec3 v);
void		cuboid_sphere_union(t_cuboid *a, const t_vec3 c, const float r);

bool		cuboid_isfinite(const t_cuboid c);

t_vec3		get_primitives_mean(const t_vector primitives);
t_vec3		get_primitives_variance(const t_vector primitives);

#endif//BVH_UTILS_H
