/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:46:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/20 04:46:54 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline float	*vec3_dot(const t_vec3 *u, const t_vec3 *v, float *result)
{
	*result = u->x * v->x + u->y * v->y + u->z * v->z;
	return (result);
}
