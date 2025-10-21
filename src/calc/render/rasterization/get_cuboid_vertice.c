/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cuboid_vertice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:26:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/10 23:26:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "bvh.h"

void	get_cuboid_vertice(t_vec3 vertices[8], t_cuboid *cuboid)
{
	vertices[0] = cuboid->min;
	vertices[1] = vec3(cuboid->max.x, cuboid->min.y, cuboid->min.z);
	vertices[2] = vec3(cuboid->max.x, cuboid->max.y, cuboid->min.z);
	vertices[3] = vec3(cuboid->min.x, cuboid->max.y, cuboid->min.z);
	vertices[4] = vec3(cuboid->min.x, cuboid->min.y, cuboid->max.z);
	vertices[5] = vec3(cuboid->max.x, cuboid->min.y, cuboid->max.z);
	vertices[6] = vec3(cuboid->max.x, cuboid->max.y, cuboid->max.z);
	vertices[7] = vec3(cuboid->min.x, cuboid->max.y, cuboid->max.z);
}
