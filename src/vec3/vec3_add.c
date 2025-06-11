/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 04:38:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/02 04:38:18 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_vec3	*vec3_add(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);

inline t_vec3	*vec3_add(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out)
{
	out->x = vec1->x + vec2->x;
	out->y = vec1->y + vec2->y;
	out->z = vec1->z + vec2->z;
	return (out);
}
