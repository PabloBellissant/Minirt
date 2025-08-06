/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/21 03:33:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font_renderer.h"

void	update_fps(t_rast_env *env);
void	draw_text(t_text *text);

static void	draw_texts(t_rast_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->text_num)
	{
		draw_text(env->texts[i]);
		i++;
	}
}

int	draw_routine(t_rast_env *env)
{
	t_mlx	*mlx;

	mlx = env->mlx;
	ft_mlx_batch_put(&mlx->img, mlx->origin, mlx->size, BACKGROUND);
	update_fps(env);
	draw_texts(env);
	draw_text(env->fps);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}
