/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_null_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 22:39:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_texture	*create_null_nmap(t_scene *scene)
{
	t_texture			tex;
	const unsigned char	normal[3] = {128, 128, 255};

	tex.pixels = malloc(1 * 3);
	if (!tex.pixels)
		return (NULL);
	ft_memcpy(tex.pixels, normal, 3);
	tex.tex_bpp = 24;
	tex.tex_size_line = 1 * 3;
	tex.width = 1;
	tex.height = 1;
	tex.name = ft_strdup("no_nmap");
	if (!tex.name)
	{
		free(tex.pixels);
		return (NULL);
	}
	if (vector_add(&scene->texture, &tex, 1) == -1)
	{
		free(tex.name);
		free(tex.pixels);
		return (NULL);
	}
	return (get_last_vector_value(&scene->texture));
}
