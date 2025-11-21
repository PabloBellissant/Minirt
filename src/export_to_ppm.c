/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_ppm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:50:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/19 00:50:43 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "calc.h"

#define COPYRIGHT "# Minirt by 'Aubry Richard Jaurel' And 'Bellissant Pablo'\n"

int	safe_putstr_fd(const char *s, int fd)
{
	return ((int)write(fd, s, ft_strlen(s)));
}

int	safe_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

static int	safe_recu_putnbr_fd(long int n, int fd)
{
	if (n > 0)
	{
		safe_recu_putnbr_fd(n / 10, fd);
		return (safe_putchar_fd(((n % 10) + '0'), fd));
	}
	return (0);
}

int	safe_putnbr_fd(int n, int fd)
{
	long int	num;

	num = (long int)(n);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (safe_recu_putnbr_fd(num, fd) == -1)
		return (-1);
	return (0);
}

int	write_header(int fd, t_img_data *img)
{
	if (safe_putstr_fd("P6\n", fd) == -1)
		return (-1);
	if (safe_putstr_fd(COPYRIGHT, fd) == -1)
		return (-1);
	if (safe_putnbr_fd(img->width * SUB_PIXEL_QUANTITY, fd) == -1)
		return (-1);
	if (safe_putchar_fd('\n', fd) == -1)
		return (-1);
	if (safe_putnbr_fd(img->height * SUB_PIXEL_QUANTITY, fd) == -1)
		return (-1);
	if (safe_putstr_fd("\n255\n", fd) == -1)
		return (-1);
	return (0);
}

int	get_percent(int value, float div)
{
	float	full_val;

	full_val = fminf((float)value / div * 100, 100.0f);
	return ((int)(full_val));
}

int	write_color(t_rgb_int color, int fd)
{
	if (write(fd, &color.r, 1) == -1)
		return (-1);
	if (write(fd, &color.g, 1) == -1)
		return (-1);
	if (write(fd, &color.b, 1) == -1)
		return (-1);
	return (0);
}

int	draw_line(t_data *data, t_camera *cam, int actual_line, int fd)
{
	t_ray		ray;
	int			pixel;
	t_object	*obj;
	t_img_data	*img;

	img = &data->mlx->img;
	pixel = 0;
	dprintf(2, "Export : %d%%\n", get_percent(actual_line, img->height * SUB_PIXEL_QUANTITY - 1));
	cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)actual_line / SUB_PIXEL_QUANTITY);
	while (pixel < img->width * SUB_PIXEL_QUANTITY)
	{
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel / SUB_PIXEL_QUANTITY);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
		ray.pos = cam->pos;
		ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
		if (write_color(rgb_ftoi(ray_path(&ray, data, &obj)), fd) == -1)
			return (-1);
		++pixel;
	}
	return (0);
}
void	fill_camera(t_camera *cam);
int	write_binary(int fd, t_data *data, int actual_line)
{
	t_camera	*cam;

	cam = &data->scene.camera;
	fill_camera(cam);
	if (draw_line(data, cam, actual_line, fd) == -1)
		return (-1);
	++actual_line;
	return (0);
}

int	export_to_ppm(t_data *data, t_mlx *mlx)
{
	static int	actual_line;

	if (actual_line == data->mlx->img.height * SUB_PIXEL_QUANTITY)
	{
		data->params.exporting = false;
		actual_line = 0;
		return (0);
	}
	if (actual_line == 0)
	{
		if (data->export_fd != -1)
			close(data->export_fd);
		data->export_fd = open("Minirt_render.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (data->export_fd == -1)
			return (-1);
		if (write_header(data->export_fd, &mlx->img) == -1)
		{
			close(data->export_fd);
			data->export_fd = -1;
			return (-1);
		}
	}
	if (write_binary(data->export_fd, data, actual_line) == -1)
	{
		close(data->export_fd);
		data->export_fd = -1;
		return (-1);
	}
	++actual_line;
	return (0);
}
