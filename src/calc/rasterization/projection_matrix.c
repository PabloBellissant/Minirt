/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:38:46 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/03 00:45:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "render.h"

t_vec2i projection_matrix(t_vec3 *p, t_camera *camera)
{
	t_vec3 temp;
	t_vec3 cam_space;
	t_vec2 projected;
	t_vec2i screen_projected;
	float fov_scale;

	temp = vec3_sub(*p, camera->pos);
	cam_space.z = vec3_dot(temp, camera->camera_forward);
	if (cam_space.z >= 0)
		return (t_vec2i){{-1, -1}};

	cam_space.x = vec3_dot(temp, camera->camera_right);
	cam_space.y = vec3_dot(temp, camera->camera_up);

	// Calculer le facteur d'échelle à partir du FOV
	fov_scale = 1.0f / tanf((camera->fov * (M_PI / 180.0f)) / 2.0f);

	projected.x = (cam_space.x * fov_scale) / (fabsf(cam_space.z) * camera->aspect_ratio);
	projected.y = (cam_space.y * fov_scale) / fabsf(cam_space.z);

	screen_projected.x = (int)((projected.x + 1.0f) * WIDTH / 2.0f);
	screen_projected.y = (int)((1.0f - projected.y) * HEIGHT / 2.0f);

	return (screen_projected);
}