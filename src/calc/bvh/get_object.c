/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:06:27 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 15:06:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

int	get_object(t_vector *obj_vec)
{
	if (obj_vec->max_elements != 0)
		return ((*(t_vec2i *)get_last_vector_value(obj_vec)).y);
	return (-1);
}
