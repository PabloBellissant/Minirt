/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:05:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/02 03:05:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cast_rays(t_camera *cam, t_ray *buffer, int pixel)
{
	int	x;
	int	y;

	x = pixel % WIDTH;
	y = pixel / WIDTH;
	cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)x);
	cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)y);
	cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
	buffer[pixel].origin = cam->pos;
	buffer[pixel].dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	buffer[pixel].id = pixel;
}
