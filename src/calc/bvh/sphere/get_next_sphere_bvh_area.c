/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_sphere_bvh_area.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:06:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 05:06:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float	get_next_sphere_bvh_area(t_sphere_bvh *a, t_sphere_bvh *b)
{
	return (vec3_length(vec3_sub(a->pos, b->pos)));
}
