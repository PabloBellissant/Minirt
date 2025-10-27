/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:55:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/09 19:55:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "render.h"

t_texture	*ppm_parser(int fd, t_texture *tex);
t_texture	*pgm_parser(int fd, t_texture *tex);
char		*skip_comment(int fd);

t_texture	texture_parser(char *texture_path)
{
	int			fd;
	t_texture	tex;
	char		*line;

	ft_bzero(&tex, sizeof(t_texture));
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (tex);
	line = skip_comment(fd);
	if (!line)
		return (tex);
	if (ft_strncmp(line, "P6", 2) == 0)
	{
		if (ppm_parser(fd, &tex) == NULL)
			return (tex);
	}
	else if (ft_strncmp(line, "P5", 2) == 0)
	{
		if (pgm_parser(fd, &tex) == NULL)
			return (tex);
	}
	free(line);
	return (tex);
}

t_texture	*create_texture(t_scene *scene, char *texture_path)
{
	t_texture	tex;

	if (scene->texture.max_elements == 0)
		vector_init(&scene->texture, sizeof(t_texture));
	ft_bzero(&tex, sizeof(t_texture));
	if (ft_strrncmp(texture_path, ".ppm", 4) == 0)
	{
		tex = texture_parser(texture_path);
		if (!tex.pixels)
			return (NULL);
	}
	if (vector_add(&scene->texture, &tex, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->texture));
}
