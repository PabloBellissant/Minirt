/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/30 19:21:03 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "struct.h"
#include "loop.h"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	key_press(int key_code, t_data *mlx)
{
	//mlx_ext_fullscreen(mlx->mlx, mlx->win, 0);
	if (key_code == XK_Escape)
		exit(1);
	if ((key_code == XK_a) || (key_code == XK_Left))
		mlx->keys.left = true;
	if ((key_code == XK_d) || (key_code == XK_Right))
		mlx->keys.right = true;
	if ((key_code == XK_w) || (key_code == XK_Up))
		mlx->keys.forward = true;
	if ((key_code == XK_s) || (key_code == XK_Down))
		mlx->keys.backward = true;
	if (key_code == XK_space)
		mlx->keys.upward = true;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		mlx->keys.downward = true;
	return (0);
}

int	key_release(int key_code, t_data *mlx)
{
	if ((key_code == XK_a) || (key_code == XK_Left))
		mlx->keys.left = false;
	if ((key_code == XK_d) || (key_code == XK_Right))
		mlx->keys.right = false;
	if ((key_code == XK_w) || (key_code == XK_Up))
		mlx->keys.forward = false;
	if ((key_code == XK_s) || (key_code == XK_Down))
		mlx->keys.backward = false;
	if (key_code == XK_space)
		mlx->keys.upward = false;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		mlx->keys.downward = false;
	return (0);
}

#include <math.h>
int mouse_move(int x, int y, t_data *mlx)
{
    static bool         first_move = true;
    static const int    center_x = WIDTH / 2;
    static const int    center_y = HEIGHT / 2;
    static const float  sensitivity = 0.002f;

    if (first_move)
    {
        mlx->mouse.last_x = center_x;
        mlx->mouse.last_y = center_y;
        first_move = false;
        mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_y);
        return (0);
    }
    
    int delta_x = x - center_x;
    int delta_y = y - center_y;
    
    // Account for screen coordinate system (Y increases downward)
    mlx->scene.camera.rot.y -= delta_x * sensitivity;  // Yaw: negative for correct left/right
    mlx->scene.camera.rot.x += delta_y * sensitivity;  // Pitch: positive because screen Y is inverted
    mlx->scene.camera.rot.z = 0.0f;                    // No roll
    
    // Clamp pitch
    const float max_pitch = M_PI * 0.49f;
    if (mlx->scene.camera.rot.x > max_pitch)
        mlx->scene.camera.rot.x = max_pitch;
    else if (mlx->scene.camera.rot.x < -max_pitch)
        mlx->scene.camera.rot.x = -max_pitch;
    
    mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_y);
    mlx->mouse.last_x = center_x;
    mlx->mouse.last_y = center_y;
    
    return (0);
}




int	loop_hook(t_data *mlx)
{
	void	*win;

	win = mlx->win;
	mlx_mouse_hide(mlx->mlx, win);
	mlx_hook(win, MotionNotify, PointerMotionMask, mouse_move, mlx);
	mlx_hook(win, KeyPress, KeyPressMask, key_press, mlx);
	mlx_hook(win, KeyRelease, KeyReleaseMask, key_release, mlx);
	//mlx_hook(win, ButtonPress, ButtonPressMask, mouse_press, mlx);
	//mlx_hook(win, ButtonRelease, ButtonReleaseMask, mouse_release, mlx);
	//mlx_hook(win, DestroyNotify, StructureNotifyMask, mlx_loop_end, mlx->mlx);
	mlx_loop_hook(mlx->mlx, loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
