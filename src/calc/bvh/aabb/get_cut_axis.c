/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cut_axis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:37:23 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 06:37:26 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int	get_cut_axis(t_aabb_bvh *parent)
{
	t_vec3	distance;

	distance = vec3_sub(parent->max, parent->min);
	if (distance.x >= distance.y && distance.x >= distance.z)
		return (0);
	if (distance.y >= distance.z)
		return (1);
	return (2);
}
