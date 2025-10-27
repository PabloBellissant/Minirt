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

t_texture	*create_null_texture(t_scene *scene)
{
	t_texture			tex;
	const unsigned char	magenta[3] = {0xFF, 0x00, 0xFF};
	const unsigned char	black[3]   = {0x00, 0x00, 0x00};

	tex.pixels = malloc(4 * 3);
	if (!tex.pixels)
		return (NULL);
	ft_memcpy(tex.pixels + 0, magenta, 3);
	ft_memcpy(tex.pixels + 3, black, 3);
	ft_memcpy(tex.pixels + 6, black, 3);
	ft_memcpy(tex.pixels + 9, magenta, 3);
	tex.tex_bpp = 24;
	tex.tex_size_line = 2 * 3;
	tex.width = 2;
	tex.height = 2;
	tex.name = ft_strdup("no_tex");
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
