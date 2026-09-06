/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 03:11:14 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 19:56:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_sphere_surface(const t_bvh_sphere sphere)
{
	return (4.f * M_PI * sphere.radius * sphere.radius);
}
