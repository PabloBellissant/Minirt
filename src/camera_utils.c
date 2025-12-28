/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:21:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/12/15 04:23:46 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>
#include "minirt.h"

// Apply rotations to the base orientation
static void	apply_rotations(t_camera *cam)
{
	cam->cos_pitch = cosf(cam->rot.x);
	cam->sin_pitch = sinf(cam->rot.x);
	cam->cos_yaw = cosf(cam->rot.y);
	cam->sin_yaw = sinf(cam->rot.y);
	cam->cos_roll = cosf(cam->rot.z);
	cam->sin_roll = sinf(cam->rot.z);
}

// Apply yaw and pitch to your base forward vector
static void	apply_yaw_and_pitch(t_camera *cam)
{
	t_vec3	temp_right;
	t_vec3	temp_up;

	cam->camera_forward = (t_vec3){{
		cam->sin_yaw * cam->cos_pitch,
		cam->sin_pitch,
		cam->cos_yaw * cam->cos_pitch
	}};
	temp_right = (t_vec3){{
		cam->cos_yaw,
		0,
		-cam->sin_yaw
	}};
	temp_up = (t_vec3){{
		-cam->sin_yaw * cam->sin_pitch,
		cam->cos_pitch,
		cam->cos_yaw * -cam->sin_pitch
	}};
	cam->camera_right = (t_vec3){{
		temp_right.x * cam->cos_roll - temp_up.x * cam->sin_roll,
		temp_right.y * cam->cos_roll - temp_up.y * cam->sin_roll,
		temp_right.z * cam->cos_roll - temp_up.z * cam->sin_roll
	}};
	
	cam->camera_up = (t_vec3){{
		temp_right.x * cam->sin_roll + temp_up.x * cam->cos_roll,
		temp_right.y * cam->sin_roll + temp_up.y * cam->cos_roll,
		temp_right.z * cam->sin_roll + temp_up.z * cam->cos_roll
	}};
}

// Create viewport vectors
static void	create_viewport_vectors(t_camera *cam)
{
	cam->u = vec3_scale(cam->camera_right, cam->viewport_width);
	cam->v = vec3_scale(cam->camera_up, -cam->viewport_height);
	cam->pixel_delta_u = vec3_div_scalar(cam->u, WIDTH);
	cam->pixel_delta_v = vec3_div_scalar(cam->v, HEIGHT);
}

// Use forward vector for focal distance
static void	create_focal_distance_viewport(t_camera *cam)
{
	cam->focal_vec = vec3_scale(cam->camera_forward, cam->focal_length);
	cam->viewport_upper_left = vec3_sub(cam->pos, cam->focal_vec);
	cam->u = vec3_div_scalar(cam->u, 2.0f);
	cam->viewport_upper_left = vec3_sub(cam->viewport_upper_left, cam->u);
	cam->v = vec3_div_scalar(cam->v, 2.0f);
	cam->viewport_upper_left = vec3_sub(cam->viewport_upper_left, cam->v);
	cam->half_pixel_offset = vec3_scale(vec3_add(cam->pixel_delta_u,
				cam->pixel_delta_v), 0.5f);
	cam->pixel00_loc = vec3_add(cam->viewport_upper_left,
			cam->half_pixel_offset);
}

void	fill_camera(t_camera *cam)
{
	cam->focal_length = 1.0f;
	cam->theta = (float)(cam->fov * M_PI) / 180.0f;
	cam->viewport_height = 2.0f * tanf(cam->theta / 2.0f) * cam->focal_length;
	cam->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	cam->viewport_width = cam->viewport_height * cam->aspect_ratio;
	apply_rotations(cam);
	apply_yaw_and_pitch(cam);
	create_viewport_vectors(cam);
	create_focal_distance_viewport(cam);
}
