/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bvh_area.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:23:14 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/30 00:23:16 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "bvh.h"

float	get_bvh_area(t_bvh *bvh)
{
	float	area;

	area = bvh->size.x * bvh->size.y;
	area += bvh->size.y * bvh->size.z;
	area += bvh->size.x * bvh->size.z;
	return (area * 2);
}
