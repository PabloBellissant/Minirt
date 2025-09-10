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

void	visible_draw(t_img_data *img, t_vec3 *v1, t_vec3 *v2, int color, t_camera *camera)
{
	t_vec2i	proj1;
	t_vec2i	proj2;

	proj1 = project_point(v1, camera);
	proj2 = project_point(v2, camera);
	if (proj1.x != -1 && proj2.x != -1)
		ft_mlx_line_put(img, proj1, proj2, color);
}

int	rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	t_vec3	vertices[8];

	vertices[0] = cuboid->min;
	vertices[1] = vec3(cuboid->max.x, cuboid->min.y, cuboid->min.z);
	vertices[2] = vec3(cuboid->max.x, cuboid->max.y, cuboid->min.z);
	vertices[3] = vec3(cuboid->min.x, cuboid->max.y, cuboid->min.z);
	vertices[4] = vec3(cuboid->min.x, cuboid->min.y, cuboid->max.z);
	vertices[5] = vec3(cuboid->max.x, cuboid->min.y, cuboid->max.z);
	vertices[6] = vec3(cuboid->max.x, cuboid->max.y, cuboid->max.z);
	vertices[7] = vec3(cuboid->min.x, cuboid->max.y, cuboid->max.z);
	draw_vertices(img, vertices, color.rgb, camera);
	return (0);
}

static void	draw_vertices(t_img_data *img, t_vec3 vertices[8], int color, t_camera *camera)
{
	visible_draw(img, &vertices[0], &vertices[1], color, camera);
	visible_draw(img, &vertices[1], &vertices[2], color, camera);
	visible_draw(img, &vertices[2], &vertices[3], color, camera);
	visible_draw(img, &vertices[3], &vertices[0], color, camera);
	visible_draw(img, &vertices[4], &vertices[5], color, camera);
	visible_draw(img, &vertices[5], &vertices[6], color, camera);
	visible_draw(img, &vertices[6], &vertices[7], color, camera);
	visible_draw(img, &vertices[7], &vertices[4], color, camera);
	visible_draw(img, &vertices[0], &vertices[4], color, camera);
	visible_draw(img, &vertices[1], &vertices[5], color, camera);
	visible_draw(img, &vertices[2], &vertices[6], color, camera);
	visible_draw(img, &vertices[3], &vertices[7], color, camera);
}
