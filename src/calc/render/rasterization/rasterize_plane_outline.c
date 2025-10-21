/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_plane_outline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:20:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 01:45:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void				rasterize_3d_line(t_img_data *img, t_3d_line *line,
						int color, t_camera *camera);
static t_vec3		get_arbitrary_vector(float normal_y);
static t_3d_line	fill_3d(t_vec3 origin, t_vec3 *pos);

#define LINE_LEN 1
#define DISTANCE 5
#define NUMBER_OF_LINES 210

void	rasterize_plane_outline(t_img_data *img, t_plane *plane,
	int color, t_camera *camera)
{
	t_3d_line	v;
	t_3d_line	line;
	t_vec2i		cross;
	t_vec3		offset;

	v.pos1 = vec3_normalize(vec3_cross(plane->normal,
				get_arbitrary_vector(plane->normal.y)));
	v.pos2 = vec3_normalize(vec3_cross(plane->normal, v.pos1));
	cross.x = -NUMBER_OF_LINES / 2;
	while (cross.x <= NUMBER_OF_LINES / 2)
	{
		cross.y = -NUMBER_OF_LINES / 2;
		while (cross.y <= NUMBER_OF_LINES / 2)
		{
			offset = vec3_add(vec3_scale(v.pos1, (float)cross.x * DISTANCE),
					vec3_scale(v.pos2, (float)cross.y * DISTANCE));
			line = fill_3d(vec3_add(plane->pos, offset), &v.pos1);
			rasterize_3d_line(img, &line, color, camera);
			line = fill_3d(vec3_add(plane->pos, offset), &v.pos2);
			rasterize_3d_line(img, &line, color, camera);
			cross.y++;
		}
		cross.x++;
	}
}

static t_3d_line	fill_3d(t_vec3 origin, t_vec3 *pos)
{
	t_3d_line	line;

	line.pos1 = vec3_add(origin, vec3_scale(*pos, LINE_LEN));
	line.pos2 = vec3_add(origin, vec3_scale(*pos, -LINE_LEN));
	return (line);
}

static t_vec3	get_arbitrary_vector(float normal_y)
{
	if (fabsf(normal_y) > 0.99f)
		return (vec3(1, 0, 0));
	return (vec3(0, 1, 0));
}
