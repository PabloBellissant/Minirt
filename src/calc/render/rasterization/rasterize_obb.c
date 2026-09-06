/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_obb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:56:34 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 01:00:45 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

#define OBB_VERTICES 8

static void	get_obb_vertices(t_vec3 out[OBB_VERTICES], const t_bvh_obb *obb)
{
	const t_vec3	e = obb->half_extents;
	const t_vec3	local[OBB_VERTICES] = {
		(t_vec3){{-e.x, -e.y, -e.z}},
		(t_vec3){{+e.x, -e.y, -e.z}},
		(t_vec3){{+e.x, +e.y, -e.z}},
		(t_vec3){{-e.x, +e.y, -e.z}},
		(t_vec3){{-e.x, -e.y, +e.z}},
		(t_vec3){{+e.x, -e.y, +e.z}},
		(t_vec3){{+e.x, +e.y, +e.z}},
		(t_vec3){{-e.x, +e.y, +e.z}}
	};
	size_t			i;

	i = 0;
	while (i < OBB_VERTICES)
	{
		out[i] = vec3_add(obb->center, quat_rotate_vec3(obb->q, local[i]));
		i++;
	}
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

int	rasterize_obb(t_bvh_obb *obb, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	t_vec3	vertices[OBB_VERTICES];

	get_obb_vertices(vertices, obb);
	draw_vertices(img, vertices, color, camera);
	return (0);
}
