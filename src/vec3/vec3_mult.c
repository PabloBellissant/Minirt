/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:25:38 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/31 16:46:09 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	*vec3_mult(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);

inline t_vec3	*vec3_mult(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out)
{
	out->x = vec1->x * vec2->x;
	out->y = vec1->y * vec2->y;
	out->z = vec1->z * vec2->z;
	return (out);
}
