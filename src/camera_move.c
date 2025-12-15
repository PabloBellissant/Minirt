/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:24:03 by jaubry--          #+#    #+#             */
/*   Updated: 2025/12/15 04:33:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>
#include "minirt.h"

#define MOVE_SPEED 10

static void	adjust_cam(t_camera *cam, const t_vec3 *matrix, const bool add, const float step)
{
	const float	new_x = matrix->x * step;
	const float	new_z = matrix->z * step;

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

void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys)
{
	const float		step = MOVE_SPEED * (1 + data->mlx->key_input.ctrl) * data->mlx->delta_time;
	const t_vec3	camera_forward = {{
		-cam->sin_yaw,
		0,
		-cam->cos_yaw
	}};
	const t_vec3	camera_right = {{
		cam->cos_yaw,
		0,
		-cam->sin_yaw
	}};

	if (keys.forward)
		adjust_cam(cam, &camera_forward, true, step);
	if (keys.backward)
		adjust_cam(cam, &camera_forward, false, step);
	if (keys.right)
		adjust_cam(cam, &camera_right, true, step);
	if (keys.left)
		adjust_cam(cam, &camera_right, false, step);
	if (keys.upward)
		cam->pos.y += step;
	if (data->mlx->key_input.shift)
		cam->pos.y -= step;
}

#define SENSITIVITY .001f
#define ROLL_SENSITIVITY .01f
#define MAX_PITCH 1.53938043117523193F

void	handle_camera_rotation(t_data *data, const int delta_x, const int delta_y)
{
	data->scene.camera.rot.y -= (float)delta_x * SENSITIVITY;
	data->scene.camera.rot.x += (float)delta_y * SENSITIVITY;
	if (data->scene.camera.rot.x > MAX_PITCH)
		data->scene.camera.rot.x = MAX_PITCH;
	else if (data->scene.camera.rot.x < -MAX_PITCH)
		data->scene.camera.rot.x = -MAX_PITCH;
	if (data->keys.roll_left)
		data->scene.camera.rot.z -= ROLL_SENSITIVITY;
	if (data->keys.roll_right)
		data->scene.camera.rot.z += ROLL_SENSITIVITY;
}

