/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_font_renderer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/21 10:22:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font_renderer.h"

int		on_key_press(int keysym, t_mlx *mlx);
int		draw_routine(t_rast_env *env);
void	add_text(t_rast_env *env, t_text *text);
void	init_fps(t_rast_env *env, t_ttf_font *font);

static t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (kill_mlx(mlx), NULL);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "font_renderer");
	if (!mlx->win)
		return (kill_mlx(mlx), NULL);
	ft_bzero(&mlx->img, sizeof(t_img));
	mlx->img = init_img(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (kill_mlx(mlx), NULL);
	mlx->origin = new_vec2(0, 0);
	mlx->size = new_vec2(WIDTH, HEIGHT);
	return (mlx);
}

static void	setup_input_hooks(t_mlx	*mlx)
{
	mlx_hook(mlx->win, DestroyNotify,
		StructureNotifyMask, &kill_mlx, mlx);
	mlx_hook(mlx->win, KeyPress,
		KeyPressMask, &on_key_press, mlx);
}

static void	add_test(t_rast_env *env, t_ttf_font *font)
{
	t_text	*text;

	text = ft_calloc(1, sizeof(t_text));
	ft_memcpy(text->content, "test\nfeur", 5);
	text->pos = new_vec2(WIDTH / 2, HEIGHT / 2);
	text->size = 10;
	text->fg = WHITE;
	text->outline = RED;
	text->outlined = false;
	text->subpixel = true;
	text->font = font;
	text->img = &(env->mlx->img);
	add_text(env, text);
}

void	start_mainloop(t_rast_env *env, t_ttf_font *font)
{
	env->mlx = init_mlx();
	if (!env->mlx)
		return ;
	init_fps(env, font);
	add_test(env, font);
	setup_input_hooks(env->mlx);
	mlx_loop_hook(env->mlx->mlx, &draw_routine, env);
	mlx_loop(env->mlx->mlx);
	kill_mlx(env->mlx);
}
