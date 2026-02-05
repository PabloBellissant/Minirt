/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_area.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:46:51 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 16:49:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float get_area(t_vec3 min, t_vec3 max)
{
    t_vec3 d;
    d.x = max.x - min.x;
    d.y = max.y - min.y;
    d.z = max.z - min.z;
    return (2.0f * (d.x * d.y + d.y * d.z + d.z * d.x));
}

float get_cuboid_area(t_cuboid *cuboid)
{
    return (get_area(cuboid->min, cuboid->max));
}
