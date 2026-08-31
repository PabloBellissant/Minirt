/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_primitives_mean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:16:46 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 19:55:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_primitives_mean(const t_vector primitives)
{
	size_t		i;
	t_object	*objects;
	t_vec3		sum;

	if (primitives.num_elements == 0)
		return (vec3_zero());
	i = 0;
	sum = vec3_zero();
	objects = primitives.data;
	while (i < primitives.num_elements)
	{
		sum = vec3_add(sum, objects[i].centroid);
		i++;
	}
	return (vec3_div_scalar(sum, primitives.num_elements));
}
