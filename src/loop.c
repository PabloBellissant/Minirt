/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/23 05:22:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "struct.h"
#include "define.h"
#include "calc.h"
#include "threading.h"

int	loop(t_data *mlx)
{
	// int		x;
	// int		y;
	// t_ray	ray;
	// // t_vec3	u;
	// // t_vec3	v;
	//
	// ray.pos.x = 0;
	// ray.pos.y = 0;
	// ray.pos.z = 0;
	// y = 0;
	// while (y < SCREEN_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < SCREEN_WIDTH)
	// 	{
	// 		// ray.dir.x = 0;
	// 		// ray.dir.y = ;
	// 		// ray.dir.z = y;
	// 		// ray_path()
	// 		++x;
	// 	}
	// 	++y;
	// }
	//
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
