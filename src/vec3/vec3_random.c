/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_random.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 05:11:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:04:06 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	*vec3_random(t_vec3 *vec);

inline t_vec3	*vec3_random(t_vec3 *vec)
{
	vec->x = ((float) rand() / (float) RAND_MAX) * 2.0f - 1.0f;
	vec->y = ((float) rand() / (float) RAND_MAX) * 2.0f - 1.0f;
	vec->z = ((float) rand() / (float) RAND_MAX) * 2.0f - 1.0f;
	return (vec);
}
