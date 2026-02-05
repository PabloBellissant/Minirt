/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bvh_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:53:45 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 04:53:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stddef.h"
#include "minirt.h"

size_t	get_bvh_count(t_vector *objects, t_object_type type)
{
	size_t		volume_count;
	size_t		i;
	t_object	*object;

	object = objects->data;
	volume_count = 0;
	i = 0;
	while (i < objects->num_elements)
	{
		if (object[i].type == type)
			++volume_count;
		++i;
	}
	i = volume_count;
	while (i > 1)
	{
		volume_count += i / 2;
		i -= i / 2;
	}
	return (volume_count);
}
