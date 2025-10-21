/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_cylinder_outline.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:35:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/17 02:36:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "calc.h"
#include "render.h"

#define RESOLUTION 42

static void	rasterize_caps(t_img_data *img, t_cylinder *cylinder,
				int color, t_camera *camera);
static void	rasterize_faces(t_img_data *img, t_cylinder *cylinder,
				int color, t_camera *camera);

void	rasterize_cylinder_outline(t_img_data *img, t_cylinder *cylinder,
		int color, t_camera *camera)
{
	rasterize_faces(img, cylinder, color, camera);
	rasterize_caps(img, cylinder, color, camera);
}

static t_vec3	rotate_around_axis(t_vec3 p, t_vec3 u,
				float cos_theta, float sin_theta)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	term1 = vec3_scale(p, cos_theta);
	term2 = vec3_scale(u, vec3_dot(u, p) * (1 - cos_theta));
	term3 = vec3_scale(vec3_cross(u, p), sin_theta);
	return (vec3_add(vec3_add(term1, term2), term3));
}

t_vec3	rotate_point(t_vec3 pos, t_vec3 rot)
{
	const t_vec3	z_axis = vec3(0, 0, 1);
	t_vec3			rotation_axis;
	float			angle;

	rotation_axis = vec3_cross(z_axis, rot);
	rotation_axis = vec3_normalize(rotation_axis);
	angle = acosf(vec3_dot(z_axis, rot));
	return (rotate_around_axis(pos, rotation_axis, cosf(angle), sinf(angle)));
}

static void	rasterize_faces(t_img_data *img, t_cylinder *cylinder,
	int color, t_camera *camera)
{
	t_3d_line	line;
	int			i;
	float		r;

	i = 0;
	while (i < RESOLUTION)
	{
		r = ((float)i / RESOLUTION) * (M_PIf * 2);
		line.pos1.x = (cosf(r) * cylinder->radius) + cylinder->pos.x;
		line.pos1.y = (sinf(r) * cylinder->radius) + cylinder->pos.y;
		line.pos1.z = cylinder->pos.z;
		line.pos2 = line.pos1;
		line.pos2.z += cylinder->height;
		line.pos1 = rotate_point(line.pos1, cylinder->rot);
		line.pos2 = rotate_point(line.pos2, cylinder->rot);
		rasterize_3d_line(img, &line, color, camera);
		++i;
	}
}

static void	rasterize_caps(t_img_data *img, t_cylinder *cylinder,
	int color, t_camera *camera)
{
	t_3d_line	line;
	t_3d_line	rotated_line;
	int			i;
	float		r;

	i = 0;
	while (i < RESOLUTION)
	{
		r = ((float)i / RESOLUTION) * (M_PIf * 2);
		line.pos1 = vec3(cosf(r) * cylinder->radius + cylinder->pos.x,
				sinf(r) * cylinder->radius + cylinder->pos.y, cylinder->pos.z);
		r = ((float)(i + 1) / RESOLUTION) * (M_PIf * 2);
		line.pos2 = vec3(cosf(r) * cylinder->radius + cylinder->pos.x,
				sinf(r) * cylinder->radius + cylinder->pos.x, cylinder->pos.z);
		rotated_line.pos1 = rotate_point(line.pos1, cylinder->rot);
		rotated_line.pos2 = rotate_point(line.pos2, cylinder->rot);
		rasterize_3d_line(img, &rotated_line, color, camera);
		line.pos1.z += cylinder->height;
		line.pos2.z += cylinder->height;
		rotated_line.pos1 = rotate_point(line.pos1, cylinder->rot);
		rotated_line.pos2 = rotate_point(line.pos2, cylinder->rot);
		rasterize_3d_line(img, &rotated_line, color, camera);
		++i;
	}
}
