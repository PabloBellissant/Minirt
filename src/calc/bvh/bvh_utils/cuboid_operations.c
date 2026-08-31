/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:21:43 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 02:21:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_cuboid_extent(const t_cuboid cuboid)
{
	return (vec3_sub(cuboid.max, cuboid.min));
}

t_vec3	cuboid_center(const t_cuboid c)
{
	return (vec3_scale(vec3_add(c.min, c.max), 0.5f));
}

t_vec3	cuboid_half(const t_cuboid c)
{
	return (vec3_scale(vec3_sub(c.max, c.min), 0.5f));
}
