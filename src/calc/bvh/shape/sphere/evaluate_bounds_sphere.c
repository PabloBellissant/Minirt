/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_bounds_sphere.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:00:22 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:23:43 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

t_vec3	get_primitives_mean(t_vector primitives);

static inline float	get_max_distance_sphere(t_sphere sphere, t_vec3 point)
{
	return (vec3_length(vec3_sub(point, sphere.centroid)) + sphere.radius);
}

static inline float	get_max_distance_triangle(t_triangle tri, t_vec3 point)
{
	float	max_d2;

	max_d2 = 0.0f;
	max_d2 = fmaxf(max_d2, vec3_length2(vec3_sub(tri.p0.pos, point)));
	max_d2 = fmaxf(max_d2, vec3_length2(vec3_sub(tri.p1.pos, point)));
	max_d2 = fmaxf(max_d2, vec3_length2(vec3_sub(tri.p2.pos, point)));
	return (sqrtf(max_d2));
}

static inline float	get_max_distance_prim(t_object obj, t_vec3 point)
{
	if (obj.type == SPHERE)
		return (get_max_distance_sphere(obj.sphere, point));
	else if (obj.type == TRIANGLE)
		return (get_max_distance_triangle(obj.triangle, point));
	return (0.0f);
}

void	evaluate_bounds_sphere(t_bvh_sphere *new, t_vector primitives)
{
	t_vec3		center;
	size_t		i;
	float		radius;
	t_object	*objects;

	*new = (t_bvh_sphere){0};
	if (primitives.num_elements == 0)
	{
		*new = (t_bvh_sphere){.pos = vec3(0, 0, 0), .radius = 0.0f};
		return ;
	}
	i = 0;
	radius = 0;
	objects = primitives.data;
	center = get_primitives_mean(primitives);
	while (i < primitives.num_elements)
	{
		radius = fmaxf(radius, get_max_distance_prim(objects[i], center));
		i++;
	}
	*new = (t_bvh_sphere){.pos = center, .radius = radius};
}
