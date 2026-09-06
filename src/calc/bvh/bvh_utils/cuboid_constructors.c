/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_constructors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:54:56 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 19:55:11 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cuboid	cuboid_inf(void)
{
	return ((t_cuboid){.min = vec3_pinf(), .max = vec3_ninf()});
}

t_cuboid	cuboid(const t_vec3 min, const t_vec3 max)
{
	return ((t_cuboid){.min = min, .max = max});
}

t_cuboid	cuboid_zero(void)
{
	return ((t_cuboid){.min = vec3_zero(), .max = vec3_zero()});
}
