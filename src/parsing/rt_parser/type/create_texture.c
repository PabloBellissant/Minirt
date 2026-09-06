/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:55:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 06:52:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "render.h"

t_texture	*parse_texture(t_scene *scene, char *texture_path)
{
	t_texture	tex;
	int			fd;

	if (scene->texture.max_elements == 0)
		vector_init(&scene->texture, sizeof(t_texture));
	ft_bzero(&tex, sizeof(t_texture));
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (pnm_parser(fd, &tex) == NULL)
		return (NULL);
	if (vector_add(&scene->texture, &tex, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->texture));
}

t_texture	*create_texture(t_vector *vec)
{
	t_texture	tex;

	if (vec->max_elements == 0)
		vector_init(vec, sizeof(t_texture));
	ft_bzero(&tex, sizeof(t_texture));
	if (vector_add(vec, &tex, 1) == -1)
		return (NULL);
	return (get_last_vector_value(vec));
}

int	create_color_texture(t_vector *vec, t_rgb_int *color)
{
	t_texture	*tex;

	tex = create_texture(vec);
	if (!tex)
		return (-1);
	tex->pixels = malloc(3 * sizeof(uint8_t));
	if (!tex->pixels)
		return (-1);
	ft_memcpy(tex->pixels, &color->rgb, 3 * sizeof(uint8_t));
	tex->channels = 3;
	tex->line_len = 3;
	tex->width = 1;
	tex->height = 1;
	return ((int) vec->num_elements - 1);
}

int	create_gray_level_texture(t_vector *vec, unsigned char value)
{
	t_texture	*tex;

	tex = create_texture(vec);
	if (!tex)
		return (-1);
	tex->pixels = malloc(1 * sizeof(uint8_t));
	if (!tex->pixels)
		return (-1);
	ft_memcpy(tex->pixels, &value, 1);
	tex->channels = 1;
	tex->line_len = 1;
	tex->width = 1;
	tex->height = 1;
	return ((int) vec->num_elements - 1);
}
