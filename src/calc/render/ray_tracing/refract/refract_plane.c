/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:19:10 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/21 02:19:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

void	refract_plane(t_vec3 *origin, t_hit *hit)
{
	*origin = vec3_add(
			hit->hit_point, vec3_scale(hit->hit_obj->plane.normal, -EPSILON));
}
