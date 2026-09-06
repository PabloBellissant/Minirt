/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:50:09 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:24:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3_vec3.h"
#include "vec3_operations.h"
#include "bvh.h"

static inline t_vec3	world_to_local(const t_mat3 basis,
							const t_vec3 origin, const t_vec3 p)
{
	return (mat3_mul_vec3_t(basis, vec3_sub(p, origin)));
}

static inline void	mat3_project_point(t_cuboid *extent, const t_mat3 basis,
						const t_vec3 o, const t_vec3 p)
{
	cuboid_point_union(extent, world_to_local(basis, o, p));
}

static inline void	mat3_project_triangle(t_cuboid *extent, const t_mat3 basis,
						const t_vec3 o, const t_triangle t)
{
	mat3_project_point(extent, basis, o, t.p0.pos);
	mat3_project_point(extent, basis, o, t.p1.pos);
	mat3_project_point(extent, basis, o, t.p2.pos);
}

t_cuboid	mat3_project_objects(t_vector objs, const t_mat3 basis,
				const t_vec3 origin)
{
	t_cuboid	interval;
	t_object	*o;
	size_t		i;

	interval = cuboid_inf();
	o = (t_object *)objs.data;
	i = 0;
	while (i < objs.num_elements)
	{
		if (o[i].type == TRIANGLE)
			mat3_project_triangle(&interval, basis, origin, o[i].triangle);
		else if (o[i].type == SPHERE)
			cuboid_sphere_union(&interval, world_to_local(basis,
					origin, o[i].sphere.centroid), o[i].sphere.radius);
		i++;
	}
	return (interval);
}
