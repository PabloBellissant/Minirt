/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/23 05:15:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "struct.h"
#include "loop.h"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	exitt(int key_code, t_data *mlx)
{
	(void) key_code;
	(void) mlx;
	//mlx_ext_fullscreen(mlx->mlx, mlx->win, 0);
	exit(1);
}

int	loop_hook(t_data *mlx)
{
	void	*win;

	win = mlx->win;
	mlx_hook(win, KeyPress, KeyPressMask, exitt, mlx);
	//mlx_hook(win, KeyRelease, KeyReleaseMask, key_release, mlx);
	//mlx_hook(win, ButtonPress, ButtonPressMask, mouse_press, mlx);
	//mlx_hook(win, ButtonRelease, ButtonReleaseMask, mouse_release, mlx);
	//mlx_hook(win, DestroyNotify, StructureNotifyMask, mlx_loop_end, mlx->mlx);
	mlx_loop_hook(mlx->mlx, loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
