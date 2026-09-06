/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_cuboid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:08:27 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 21:19:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

static void	draw_vertices(t_img_data *img, t_vec3 vertices[8],
				t_rgb_int color, t_camera *cam);

int	rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	t_vec3	vertices[8];

	get_cuboid_vertice(vertices, cuboid);
	draw_vertices(img, vertices, color, camera);
	return (0);
}

static void	draw_vertices(t_img_data *img, t_vec3 vertices[8],
	t_rgb_int color, t_camera *cam)
{
	rasterize_3d_line(img, &(t_3d_line){vertices[0], vertices[1]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[1], vertices[2]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[2], vertices[3]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[3], vertices[0]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[4], vertices[5]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[5], vertices[6]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[6], vertices[7]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[7], vertices[4]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[0], vertices[4]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[1], vertices[5]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[2], vertices[6]}, color, cam);
	rasterize_3d_line(img, &(t_3d_line){vertices[3], vertices[7]}, color, cam);
}
