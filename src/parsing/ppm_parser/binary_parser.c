/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:11:10 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 02:11:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	check_header(int fd, int *width, int *height, int *bit);
int	get_binary_data(int fd, t_texture *tex);

t_texture	*pgm_parser(const int fd, t_texture *tex)
{
	if (check_header(fd, &tex->width, &tex->height, &tex->tex_bpp) == -1)
		return (NULL);
	if (get_binary_data(fd, tex) == -1)
		return (NULL);
	return (tex);
}

int	get_binary_data(int fd, t_texture *tex)
{
	ssize_t	ret_val;
	ssize_t	size;

	size = (ssize_t) tex->width * (size_t) tex->height;
	tex->tex_size_line = tex->width;
	tex->tex_bpp = 8;
	tex->pixels = malloc(size);
	if (!tex->pixels)
		return (-1);
	ret_val = read(fd, tex->pixels, size);
	if (ret_val != size)
	{
		free(tex->pixels);
		tex->pixels = NULL;
		return (-1);
	}
	return (0);
}
