/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:11:40 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/05 00:11:40 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "parsing.h"

t_vec3	vec3_negate(t_vec3 v);
float	rand_f(void);

t_vec3	sample_hemisphere_uniform(t_vec3 normal)
{
	t_vec3	random_dir;

	random_dir = vec3_rand();
	random_dir = vec3_normalize(random_dir);
	if (vec3_dot(random_dir, normal) < 0.0f)
		random_dir = vec3_negate(random_dir);
	return (random_dir);
}

t_vec3	vec3_rand(void)
{
	t_vec3	rand_vec;

	rand_vec.x = 2.0f * rand_f() - 1.0f;
	rand_vec.y = 2.0f * rand_f() - 1.0f;
	rand_vec.z = 2.0f * rand_f() - 1.0f;
	return (rand_vec);
}

t_vec3	vec3_rand_in_sphere(float sphere_radius)
{
	t_vec3	rand_vec;

	rand_vec = vec3_rand();
	while (vec3_length2(rand_vec) > 1)
		rand_vec = vec3_rand();
	return (vec3_scale(vec3_normalize(rand_vec), sphere_radius));
}
