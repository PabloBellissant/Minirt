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

int	check_header(int fd, int *width, int *height, int *bit)
{
	char	*line;

	line = get_next_line(fd);
	if (ft_strncmp(line, "P6", 2) != 0)
	{
		dprintf(2, "Line : '%s'\n", line);
		free(line);
		ft_putstr_fd("Error\n Unsupported .ppm texture\n", 2);
		return (-1);
	}
	free(line);
	line = get_next_line(fd);
	if (!line || ft_scan(2, " *%d  *%d *\n", line, width, height) != 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	line = get_next_line(fd);
	if (!line || ft_scan(3, " *%d *\n", line, bit) != 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

int get_data(int fd, t_texture *tex)
{
	ssize_t	ret_val;
	size_t	size;

	size = (size_t) tex->width * (size_t) tex->height * 3;
	tex->tex_size_line = tex->width * 3;
	tex->tex_bpp = 24;

	tex->pixels = malloc(size);
	if (!tex->pixels)
		return (-1);

	ret_val = read(fd, tex->pixels, size);
	if (ret_val < 0)
	{
		free(tex->pixels);
		tex->pixels = NULL;
		return (-1);
	}
	return (0);
}

t_texture	ppm_parser(char *texture_path)
{
	int			fd;
	t_texture	tex;

	ft_bzero(&tex, sizeof(t_texture));
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (tex);
	if (check_header(fd, &tex.width, &tex.height, &tex.tex_bpp) == -1)
	{
		close(fd);
		return (tex);
	}
	if (get_data(fd, &tex) == -1)
	{
		close(fd);
		return (tex);
	}
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
		tex = ppm_parser(texture_path);
		if (!tex.pixels)
			return (NULL);
	}
	if (vector_add(&scene->texture, &tex, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->texture));
}
