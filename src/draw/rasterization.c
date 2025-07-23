/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:21:27 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/23 01:30:35 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "define.h"
#include "draw.h"

void	rasterization(t_data *mlx)
{
	t_scene		*scene;
	t_object	*object;
	size_t		i;
	t_vec3		temp;
	t_vec3		temp2;
	t_sphere	*sphere;

	scene = &mlx->scene;
	object = scene->objects.data;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (object[i].type != SPHERE)
		{
			++i;
			continue;
		}
		sphere = &object[i].sphere;
		temp = sphere->pos;
		float	x_proj = (temp.x / temp.z) * 565;
		float	y_proj = (temp.y / temp.z) * 565;
		t_vec2i vec1 = (t_vec2i) {x_proj + WIDTH / 2, y_proj + HEIGHT / 2};
		temp2 = sphere->pos;
		temp2.x += sphere->diameter / 2;
		float x_proj2 = (temp2.x / temp2.z) * 570;
		float y_proj2 = (temp2.y / temp2.z) * 570;
		t_vec2i vec2 = (t_vec2i) {x_proj2 + WIDTH / 2, y_proj2 + HEIGHT / 2};
		draw_line(mlx, vec1, vec2);
		++i;
	}
}

//		t_vec3	temp;
//		temp.x = tab[t].pos.x + obj.translation.x;
// 		temp.y = tab[t].pos.y + obj.translation.y;
// 		temp.z = tab[t].pos.z + obj.translation.z;
// 		t_vec3 p = mat3_apply(rot, temp);
// 		p.z += 1.5;
// 		p.y *= -1;
// 		float	x_proj = (p.x / p.z) * 800;
// 		float	y_proj = (p.y / p.z) * 800;
// 		int x_screen = x_proj + WIDTH / 2;
// 		int y_screen = y_proj + HEIGHT / 2;
// 		safe_put_pixel(mlx->addr, x_screen, y_screen, 0x00FFFF);