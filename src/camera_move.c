/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:24:03 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:28:27 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "vectors.h"
#include <math.h>
#include "minirt.h"

#define MOVE_SPEED 0.1f

static void	adjust_cam(t_camera *cam, const t_vec3 *matrix, const bool add)
{
	const float	new_x = matrix->x * MOVE_SPEED;
	const float	new_z = matrix->z * MOVE_SPEED;

	if (add)
	{
		cam->pos.x += new_x;
		cam->pos.z += new_z;
	}
	else
	{
		cam->pos.x -= new_x;
		cam->pos.z -= new_z;
	}
}

void	handle_camera_move(t_camera *cam, t_keys keys)
{
	const t_vec3	camera_forward = {{{
		-cam->sin_yaw,
		0,
		-cam->cos_yaw
	}}};
	const t_vec3	camera_right = {{{
		cam->cos_yaw,
		0,
		-cam->sin_yaw
	}}};

	if (keys.forward)
		adjust_cam(cam, &camera_forward, true);
	if (keys.backward)
		adjust_cam(cam, &camera_forward, false);
	if (keys.right)
		adjust_cam(cam, &camera_right, true);
	if (keys.left)
		adjust_cam(cam, &camera_right, false);
	if (keys.upward)
		cam->pos.y += MOVE_SPEED;
	if (keys.downward)
		cam->pos.y -= MOVE_SPEED;
}
