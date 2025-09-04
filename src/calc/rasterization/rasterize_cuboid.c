/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_cuboid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:08:27 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/04 06:12:17 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

static void	draw_vertices(t_vec2i vertices[8], t_img_data *img, int color);

int	rasterize_cuboid(t_cuboid *c, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	t_vec3	vertices[8];
	t_vec2i	projected[8];
	int		i;

	vertices[0] = c->pos;
	vertices[1] = vec3(c->pos.x + c->size.x, c->pos.y, c->pos.z);
	vertices[2] = vec3(c->pos.x + c->size.x, c->pos.y + c->size.y, c->pos.z);
	vertices[3] = vec3(c->pos.x, c->pos.y + c->size.y, c->pos.z);
	vertices[4] = vec3(c->pos.x, c->pos.y, c->pos.z + c->size.z);
	vertices[5] = vec3(c->pos.x + c->size.x, c->pos.y, c->pos.z + c->size.z);
	vertices[6] = vec3(c->pos.x + c->size.x,
			c->pos.y + c->size.y, c->pos.z + c->size.z);
	vertices[7] = vec3(c->pos.x, c->pos.y + c->size.y, c->pos.z + c->size.z);
	i = 0;
	while (i < 8)
	{
		projected[i] = project_point(&vertices[i], camera);
		++i;
	}
	draw_vertices(projected, img, color.rgb);
	return (0);
}

static void	draw_vertices(t_vec2i vertices[8], t_img_data *img, int color)
{
	ft_mlx_line_put(img, vertices[0], vertices[1], color);
	ft_mlx_line_put(img, vertices[1], vertices[2], color);
	ft_mlx_line_put(img, vertices[2], vertices[3], color);
	ft_mlx_line_put(img, vertices[3], vertices[0], color);
	ft_mlx_line_put(img, vertices[4], vertices[5], color);
	ft_mlx_line_put(img, vertices[5], vertices[6], color);
	ft_mlx_line_put(img, vertices[6], vertices[7], color);
	ft_mlx_line_put(img, vertices[7], vertices[4], color);
	ft_mlx_line_put(img, vertices[0], vertices[4], color);
	ft_mlx_line_put(img, vertices[1], vertices[5], color);
	ft_mlx_line_put(img, vertices[2], vertices[6], color);
	ft_mlx_line_put(img, vertices[3], vertices[7], color);
}
