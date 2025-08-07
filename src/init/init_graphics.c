/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:51:51 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "minirt.h"
#include "font_renderer.h"
#include "libft.h"
#include "mlx_wrapper.h"

#define FONT_PATH "/home/jaubry--/Downloads/JetBrainsMono-2.304/fonts/ttf/Jet\
BrainsMono-Regular.ttf"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

void	disable_decorations(Display *d, Window w)
{
	struct MotifWmHints	hints;
	Atom				prop;

	hints.flags = CWBackPixel;
	hints.decorations = 0;
	prop = XInternAtom(d, "_MOTIF_WM_HINTS", False);
	XChangeProperty(d, w, prop, prop, 32, PropModeReplace,
		(unsigned char *)&hints, 5);
}

static int	get_fps(void)
{
	static ssize_t	last_time = -1;
	static ssize_t	result = 0;
	static ssize_t	fc = 0;

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

t_rast_env	*init_font_rasterizer(t_mlx *mlx)
{
	t_ttf_font	*font;
	t_rast_env	*env;

	font = NULL;
	if (init_ttf(FONT_PATH, &font))
		return (NULL);
	env = ft_calloc(sizeof(t_rast_env), 1);
	if (!env)
		return (NULL);
	env->mlx = mlx;
	if (!env->mlx)
		return (NULL);
	if (init_fps(env, font) != 0)
		return (NULL);
	return (env);
}

int	init_graphics(t_data *data)
{
	data->mlx = init_mlx(WIDTH, HEIGHT, TITLE);
	if (!data->mlx)
		return (-1);
	if (WINDOWLESS || FULLSCREEN)
		disable_decorations(data->mlx->mlx->display, data->mlx->win->window);
	if (FULLSCREEN)
		mlx_ext_fullscreen(data->mlx->mlx, data->mlx->win, 1);
	data->fullscreen = FULLSCREEN;//to move
	data->font_env = init_font_rasterizer(data->mlx);
	if (!data->font_env)
		return (-1);
	data->screen.x = WIDTH;
	data->screen.y = HEIGHT;
	return (0);
}
