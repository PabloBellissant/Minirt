/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:21:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 09:48:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>
#include "minirt.h"

// Apply rotations to the base orientation
static void	apply_rotations(t_camera *cam)
{
	cam->cos_pitch = cos(cam->rot.x);
	cam->sin_pitch = sin(cam->rot.x);
	cam->cos_yaw = cos(cam->rot.y);
	cam->sin_yaw = sin(cam->rot.y);
}

// Apply yaw and pitch to your base forward vector
static void	apply_yaw_and_pitch(t_camera *cam)
{
	cam->camera_forward = (t_vec3){{
		cam->sin_yaw * cam->cos_pitch,
		cam->sin_pitch,
		cam->cos_yaw * cam->cos_pitch
	}};
	cam->camera_right = (t_vec3){{
		cam->cos_yaw,
		0,
		-cam->sin_yaw
	}};
	cam->camera_up = (t_vec3){{
		-cam->sin_yaw * cam->sin_pitch,
		cam->cos_pitch,
		cam->cos_yaw * -cam->sin_pitch
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
	cam->theta = (cam->fov * M_PI) / 180.0f;
	cam->viewport_height = 2.0f * tan(cam->theta / 2.0f) * cam->focal_length;
	cam->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	cam->viewport_width = cam->viewport_height * cam->aspect_ratio;
	apply_rotations(cam);
	apply_yaw_and_pitch(cam);
	create_viewport_vectors(cam);
	create_focal_distance_viewport(cam);
}
