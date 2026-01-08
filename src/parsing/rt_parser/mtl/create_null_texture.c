/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_null_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 06:52:37 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

int	create_null_texture(t_vector *vec)
{
	t_texture			*tex;
	const unsigned char	magenta[3] = {0xFF, 0x00, 0xFF};
	const unsigned char	black[3]   = {0x00, 0x00, 0x00};
	int					texture_id;

	texture_id = get_texture(vec, "no_tex");
	if (texture_id != -1)
		return (texture_id);
	tex = create_texture(vec);
	if (!tex)
		return (-1);
	tex->pixels = malloc(4 * 3);
	if (!tex->pixels)
		return (-1);
	ft_memcpy(tex->pixels + 0, magenta, 3);
	ft_memcpy(tex->pixels + 3, black, 3);
	ft_memcpy(tex->pixels + 6, black, 3);
	ft_memcpy(tex->pixels + 9, magenta, 3);
	tex->channels = 3;
	tex->line_len = 2 * 3;
	tex->width = 2;
	tex->height = 2;
	tex->name = ft_strdup("no_tex");
	if (!tex->name)
		return (-1);
	return ((int) vec->num_elements - 1);
}
