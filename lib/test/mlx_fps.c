/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 01:52:47 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/17 23:40:43 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "font_renderer.h"

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

void	init_fps(t_rast_env *env, t_ttf_font *font)
{
	t_text	*fps;

	fps = ft_calloc(1, sizeof(t_text));
	fps->pos = new_vec2(0, 20);
	fps->fg = YELLOW;
	fps->size = 20;
	fps->img = &(env->mlx->img);
	fps->font = font;
	fps->subpixel = true;
	env->fps = fps;
}

void	update_fps(t_rast_env *env)
{
	ft_itoal(get_fps(), env->fps->content);
}
