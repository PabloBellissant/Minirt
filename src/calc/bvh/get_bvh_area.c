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

float	get_bvh_area(t_bvh *bvh)
{
	float	area;

	area = bvh->size.x * bvh->size.y;
	area += bvh->size.y * bvh->size.z;
	area += bvh->size.x * bvh->size.z;
	return (area * 2);
}
