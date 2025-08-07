/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 00:00:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "minirt.h"
#include "font_renderer.h"

#define FONT_PATH "/home/jaubry--/Downloads/JetBrainsMono-2.304/fonts/ttf/Jet\
BrainsMono-Regular.ttf"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

void	disable_decorations(Display *d, Window w)
{
	struct MotifWmHints	hints;
	Atom				prop;

	hints.flags = (1L << 1);//find define
	hints.decorations = 0;
	prop = XInternAtom(d, "_MOTIF_WM_HINTS", False);
	XChangeProperty(d, w, prop, prop, 32, PropModeReplace,
		(unsigned char *)&hints, 5);
}

int	init_img(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits,
			&data->line_len, &data->endian);
	return (0);
}

t_mlx	*init_mlx(t_data *data)
{
	t_mlx		*mlx;
	t_img_data	img;

	mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!mlx)
		return (NULL);
	img.img = data->img;
	img.addr = data->addr;
	img.byte_depth = data->bits;
	img.line_len = data->line_len;
	img.endian = data->endian;
	img.width = data->screen.x;
	img.height = data->screen.y;
	mlx->mlx = data->mlx;
	mlx->win = data->win;
	mlx->img = img;
	mlx->origin = vec2i(0, 0);
	mlx->size = vec2i(WIDTH, HEIGHT);
	return (mlx);
}

ssize_t	get_current_time(void);

static int	get_fps(void)
{
	static ssize_t	last_time = -1;
	static ssize_t	fc = 0;
	static ssize_t	result = 0;

	fc++;
	if (last_time == -1)
		last_time = get_current_time();
	if (get_current_time() >= last_time + 1000)
	{
		last_time = get_current_time();
		result = fc;
		fc = 0;
	}
	return (result);
}

static size_t	ft_itoalen(long int nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	ft_itoal(int n, char *str)
{
	long int	num;
	size_t		i;
	size_t		len;

	i = 0;
	num = (long int)n;
	len = ft_itoalen(num);
	str[len] = '\0';
	str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[len - i - 1] = '0' + (num % 10);
		num /= 10;
		i++;
	}
}

void	update_fps(t_rast_env *env)
{
	ft_itoal(get_fps(), env->fps->content);
}


int	init_fps(t_rast_env *env, t_ttf_font *font)
{
	t_text	*fps;

	fps = ft_calloc(1, sizeof(t_text));
	if (!fps)
		return (-1);
	fps->pos = vec2i(0, 20);
	fps->fg = YELLOW;
	fps->size = 20;
	fps->img = &(env->mlx->img);
	fps->font = font;
	fps->subpixel = true;
	env->fps = fps;
	return (0);
}

t_rast_env	*init_font_rasterizer(t_data *data)
{
	t_ttf_font	*font;
	t_rast_env	*env;

	font = NULL;
	if ( init_ttf(FONT_PATH, &font))
		return (NULL);
	env = ft_calloc(sizeof(t_rast_env), 1);
	if (!env)
		return (NULL);
	env->mlx = init_mlx(data);
	if (!env->mlx)
		return (NULL);
	if (init_fps(env, font) != 0)
		return (NULL);
	return (env);
}

int	init_graphics(t_data *data)
{
	data->screen.x = WIDTH;
	data->screen.y = HEIGHT;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	if (WINDOWLESS || FULLSCREEN)
		disable_decorations(data->mlx->display, data->win->window);
	if (FULLSCREEN)
		mlx_ext_fullscreen(data->mlx, data->win, 1);
	data->fullscreen = FULLSCREEN;
	init_img(data);
	data->font_env = init_font_rasterizer(data);
	if (!data->font_env)
		return (-1);
	return (0);
}
