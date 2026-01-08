/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:01:04 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/08 00:03:42 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

t_vec3	sample_hemisphere_uniform(t_vec3 normal);

float	rand_f(void)
{
	return ((float) rand() / (float) RAND_MAX);
}

t_vec3	random_point_in_triangle(t_triangle *triangle)
{
	float	r1;
	float	r2;
	float	s;
	t_vec3	point;

	r1 = rand_f();
	r2 = rand_f();
	s = sqrtf(r1);
	point = vec3_add(vec3_add(
				vec3_scale(triangle->p0.pos, 1 - s),
				vec3_scale(triangle->p1.pos, s * (1 - r2))),
			vec3_scale(triangle->p2.pos, s * r2));
	return (point);
}

t_light	get_emissive(t_object *object, t_mat *mat, t_vec3 hit_point)
{
	t_light	light;
	t_vec3	normal;

	light.rgb = mat[object->mat_id].ke;
	if (object->type == SPHERE)
	{
		normal = vec3_sub(hit_point, object->sphere.pos);
		light.pos = vec3_add(object->sphere.pos, vec3_scale(
					sample_hemisphere_uniform(normal),
					object->sphere.diameter / 1.95f));
		light.rgb = vec3_scale(light.rgb, object->sphere.diameter);
	}
	else
	{
		light.pos = random_point_in_triangle(&object->triangle);
		normal = vec3_sub(hit_point, light.pos);
		light.pos = vec3_add(light.pos, vec3_scale(normal, 0.01f));
		light.rgb = vec3_scale(light.rgb, vec3_length(vec3_cross(
						object->triangle.edge_p1p0,
						object->triangle.edge_p2p0)) * 0.5f);
	}
	return (light);
}

t_light	get_random_light(t_scene *scene, int total_lights, t_vec3 hit_point)
{
	t_light		light;
	int			random;
	t_object	*object;

	random = rand() % total_lights;
	if (random >= (int) scene->lights.num_elements)
	{
		object = get_vector_value(&scene->objects,
				scene->emissive_id[random - scene->lights.num_elements]);
		return (get_emissive(object, scene->mat.data, hit_point));
	}
	object = get_vector_value(&scene->lights, random);
	light.pos = object->light.pos;
	light.rgb = vec3_scale(object->light.rgb, 5);
	return (light);
}
