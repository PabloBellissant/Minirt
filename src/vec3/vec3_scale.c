/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:29:12 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/02 05:29:14 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

inline t_vec3*	vec3_scale(t_vec3 *vec, const double t)
{
	vec->x *= t;
	vec->y *= t;
	vec->z *= t;
	return (vec);
}
