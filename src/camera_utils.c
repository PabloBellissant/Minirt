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

#include "vec3_scalar.h"
#include "vectors.h"
#include <math.h>
#include "minirt.h"

static void	apply_yaw_and_pitch(t_camera *cam)
{
	t_vec3	temp_right;
	t_vec3	temp_up;

	cam->camera_forward = (t_vec3){{
		sinf(cam->rot.y) * cosf(cam->rot.x),
		sinf(cam->rot.x),
		cosf(cam->rot.y) * cosf(cam->rot.x)
	}};
	temp_right = (t_vec3){{cosf(cam->rot.y), 0, -sinf(cam->rot.y)}};
	temp_up = (t_vec3){{
		-sinf(cam->rot.y) * sinf(cam->rot.x),
		cosf(cam->rot.x),
		cosf(cam->rot.y) * -sinf(cam->rot.x)
	}};
	cam->camera_right = (t_vec3){{
		temp_right.x * cosf(cam->rot.z) - temp_up.x * sinf(cam->rot.z),
		temp_right.y * cosf(cam->rot.z) - temp_up.y * sinf(cam->rot.z),
		temp_right.z * cosf(cam->rot.z) - temp_up.z * sinf(cam->rot.z)
	}};
	cam->camera_up = vec3_add(
			vec3_scale(temp_right, sinf(cam->rot.z)),
			vec3_scale(temp_up, cosf(cam->rot.z)));
}

static void	create_focal_distance_viewport(
		t_camera *cam, cl_float3 u, cl_float3 v)
{
	cl_float3	viewport_upper_left;
	cl_float3	half_pixel_offset;

	viewport_upper_left = vec3_sub(cam->pos, cam->camera_forward);
	u = vec3_div_scalar(u, 2.0f);
	viewport_upper_left = vec3_sub(viewport_upper_left, u);
	v = vec3_div_scalar(v, 2.0f);
	viewport_upper_left = vec3_sub(viewport_upper_left, v);
	half_pixel_offset = vec3_scale(vec3_add(cam->pixel_delta_u,
				cam->pixel_delta_v), 0.5f);
	cam->pixel00_loc = vec3_add(viewport_upper_left,
			half_pixel_offset);
}

static void	create_viewport_vectors(
	t_camera *cam, t_img_data *img, float viewport_height, float viewport_width)
{
	cl_float3	u;
	cl_float3	v;

	u = vec3_scale(cam->camera_right, viewport_width);
	v = vec3_scale(cam->camera_up, -viewport_height);
	cam->pixel_delta_u = vec3_div_scalar(u, img->width);
	cam->pixel_delta_v = vec3_div_scalar(v, img->height);
	create_focal_distance_viewport(cam, u, v);
}

void	fill_camera(t_camera *cam, t_img_data *img)
{
	float	viewport_height;
	float	viewport_width;

	viewport_height = 2.0f * tanf((cam->fov * M_PI) / 180 / 2.0f);
	viewport_width = viewport_height * ((float)img->width / (float)img->height);
	apply_yaw_and_pitch(cam);
	create_viewport_vectors(cam, img, viewport_height, viewport_width);
}
