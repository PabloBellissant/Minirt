/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_scalar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:31:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/02 05:31:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

inline t_vec3*	vec3_add_scalar(t_vec3 *vec, const double x)
{
	vec->x += x;
	vec->y += x;
	vec->z += x;
	return (vec);
}
