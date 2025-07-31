/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:08:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 16:45:06 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_vec3	*vec3_sub(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);

inline t_vec3	*vec3_sub(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out)
{
	out->x = vec1->x - vec2->x;
	out->y = vec1->y - vec2->y;
	out->z = vec1->z - vec2->z;
	return (out);
}
