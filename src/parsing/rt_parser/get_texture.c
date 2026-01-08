/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:11:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/10 00:11:07 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_texture(t_vector *texture, char *texture_name)
{
	size_t		i;
	t_texture	*actual;

	actual = texture->data;
	i = 0;
	while (i < texture->num_elements)
	{
		if (actual[i].name && ft_strcmp(texture_name, actual[i].name) == 0)
			return ((int) i);
		++i;
	}
	return (-1);
}

