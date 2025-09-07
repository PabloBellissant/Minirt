/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bvh_area.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:23:14 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:22 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_bvh_area(t_cuboid *cuboid)
{
	float	area;
	t_vec3	size;

	size.x = cuboid->max.x - cuboid->min.x;
	size.y = cuboid->max.y - cuboid->min.y;
	size.z = cuboid->max.z - cuboid->min.z;
	area = size.x * size.y;
	area += size.y * size.z;
	area += size.x * size.z;
	return (area);
}
