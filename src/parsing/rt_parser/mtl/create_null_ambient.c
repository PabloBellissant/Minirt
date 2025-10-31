/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_null_ambient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 22:39:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_texture	*create_null_ambient(t_vector *vec)
{
	t_texture			*tex;

	tex = create_texture(vec);
	if (!tex)
		return (NULL);
	tex->pixels = malloc(1);
	if (!tex->pixels)
		return (NULL);
	tex->pixels[0] = (char) 255;
	tex->tex_bpp = 8;
	tex->tex_size_line = 1;
	tex->width = 1;
	tex->height = 1;
	tex->name = ft_strdup("no_ambient");
	if (!tex->name)
		return (NULL);
	return (tex);
}
