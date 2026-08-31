/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_primitives_variance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:17:20 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 20:20:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_primitives_variance(const t_vector primitives)
{
	const t_vec3	mean = get_primitives_mean(primitives);
	t_vec3			variance;
	t_object		*objects;
	size_t			i;
	t_vec3			d;

	if (primitives.num_elements == 0)
		return (vec3_zero());
	i = 0;
	objects = primitives.data;
	variance = vec3_zero();
	while (i < primitives.num_elements)
	{
		d = vec3_sub(objects[i].centroid, mean);
		variance.x += d.x * d.x;
		variance.y += d.y * d.y;
		variance.z += d.z * d.z;
		i++;
	}
	return (vec3_div_scalar(variance, primitives.num_elements));
}
