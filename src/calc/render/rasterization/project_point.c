/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:38:46 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/09 01:35:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "render.h"
#include <math.h>

#define NEAR_EPS 1e-2f

static inline int	compute_cam_space(const t_vec3 temp, const t_camera *cam,
						t_vec3 *cs, float *d)
{
	cs->z = vec3_dot(temp, cam->camera_forward);
	if (!isfinite(cs->z))
		return (0);
	*d = -cs->z;
	if (*d < NEAR_EPS)
		return (0);
	cs->x = vec3_dot(temp, cam->camera_right);
	cs->y = vec3_dot(temp, cam->camera_up);
	return (vec3_isfinite(*cs));
}

static inline int	compute_fov_scale(const t_camera *camera, float *fov_scale)
{
	float	fov_rad;

	if ((camera->fov <= 0) || (camera->fov >= 179))
		return (0);
	fov_rad = (camera->fov * (float)M_PI / 180.0f) * 0.5f;
	*fov_scale = 1.0f / tanf(fov_rad);
	return (isfinite(*fov_scale));
}

static inline t_vec2i	ndc_to_screen(const t_vec2 projected,
							const t_img_data *img)
{
	t_vec2i	screen;

	screen.x = (int)((projected.x + 1.0f) * (float)img->width * 0.5f);
	screen.y = (int)((1.0f - projected.y) * (float)img->height * 0.5f);
	return (screen);
}

t_vec2i	project_point(const t_vec3 *p, const t_camera *camera,
			const t_img_data *img)
{
	t_vec3	cam_space;
	t_vec2	projected;
	float	fov_scale;
	float	depth;
	float	aspect;

	if ((img->height <= 0) || (img->width <= 0))
		return (vec2i_err());
	if (!compute_fov_scale(camera, &fov_scale))
		return (vec2i_err());
	if (!compute_cam_space(vec3_sub(*p, camera->pos), camera,
			&cam_space, &depth))
		return (vec2i_err());
	aspect = (float)img->width / (float)img->height;
	projected.x = (cam_space.x * fov_scale) / (depth * aspect);
	projected.y = (cam_space.y * fov_scale) / depth;
	if (!vec2_isfinite(projected))
		return (vec2i_err());
	return (ndc_to_screen(projected, img));
}
