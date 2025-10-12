/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:34:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 06:34:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "minirt.h"

void	set_size(t_aabb_bvh *bvh, t_vector *objects_vec)
{
	size_t		i;
	t_object	**objects;
	t_vec3		temp_min;
	t_vec3		temp_max;

	bvh->min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	bvh->max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	objects = objects_vec->data;
	i = 0;
	while (i < objects_vec->num_elements)
	{
		get_min_max(objects[i], &temp_min, &temp_max);
		bvh->min.x = fminf(bvh->min.x, temp_min.x);
		bvh->min.y = fminf(bvh->min.y, temp_min.y);
		bvh->min.z = fminf(bvh->min.z, temp_min.z);
		bvh->max.x = fmaxf(bvh->max.x, temp_max.x);
		bvh->max.y = fmaxf(bvh->max.y, temp_max.y);
		bvh->max.z = fmaxf(bvh->max.z, temp_max.z);
		++i;
	}
}
