/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_ppm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:50:41 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/19 14:46:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "export.h"
#include <fcntl.h>

#define COPYRIGHT "# Minirt by 'Aubry Richard Jaurel' And 'Bellissant Pablo'"

static int	write_header(int fd, t_img_data *img);
static int	write_color(t_rgb_int color, int fd);
static int	write_binary(int fd, t_data *data);

void	export_to_ppm(t_data *data, t_mlx *mlx)
{
	int	fd;

	fd = open("Minirt_render.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
		return ;
	if (write_header(fd, &mlx->img) == -1)
	{
		close(fd);
		return ;
	}
	if (write_binary(fd, data) == -1)
	{
		close(fd);
		return ;
	}
	close(fd);
	return ;
}

static int	write_header(int fd, t_img_data *img)
{
	if (dprintf(fd, "P6\n%s\n%ld\n%ld\n255\n",
			COPYRIGHT, img->width, img->height) == -1)
	{
		return (-1);
	}
	return (0);
}

static int	write_color(t_rgb_int color, int fd)
{
	if (write(fd, &color.r, 1) == -1)
		return (-1);
	if (write(fd, &color.g, 1) == -1)
		return (-1);
	if (write(fd, &color.b, 1) == -1)
		return (-1);
	return (0);
}

static int	write_binary(int fd, t_data *data)
{
	ssize_t		i;
	t_rgb_int	temp;

	i = 0;
	while (i < data->mlx->img.width * data->mlx->img.height)
	{
		temp.rgb = data->buffers.addr[i];
		if (write_color(temp, fd) == -1)
			return (-1);
		++i;
	}
	return (0);
}
