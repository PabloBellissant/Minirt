/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_cuboid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:08:27 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 04:56:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

static void	draw_vertices(t_img_data *img, t_vec3 vertices[8], int color, t_camera *camera);

int	rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	t_vec3	vertices[8];

	get_cuboid_vertice(vertices, cuboid);
	draw_vertices(img, vertices, (int)color.rgb, camera);
	return (0);
}

static void	draw_vertices(t_img_data *img, t_vec3 vertices[8], int color, t_camera *camera)
{
	draw_only_visible(img, &vertices[0], &vertices[1], color, camera);
	draw_only_visible(img, &vertices[1], &vertices[2], color, camera);
	draw_only_visible(img, &vertices[2], &vertices[3], color, camera);
	draw_only_visible(img, &vertices[3], &vertices[0], color, camera);
	draw_only_visible(img, &vertices[4], &vertices[5], color, camera);
	draw_only_visible(img, &vertices[5], &vertices[6], color, camera);
	draw_only_visible(img, &vertices[6], &vertices[7], color, camera);
	draw_only_visible(img, &vertices[7], &vertices[4], color, camera);
	draw_only_visible(img, &vertices[0], &vertices[4], color, camera);
	draw_only_visible(img, &vertices[1], &vertices[5], color, camera);
	draw_only_visible(img, &vertices[2], &vertices[6], color, camera);
	draw_only_visible(img, &vertices[3], &vertices[7], color, camera);
}
