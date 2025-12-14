/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:05:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/14 00:20:13 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cast_rays(t_camera *cam, t_ray *rays, t_hit *hits, int pixel)
{
	int	x;
	int	y;

	x = pixel % WIDTH;
	y = pixel / WIDTH;
	cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)x);
	cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)y);
	cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
	rays[pixel].origin = cam->pos;
	rays[pixel].dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	rays[pixel].accumulated_color = rgb(0, 0, 0);
	rays[pixel].iteration = 0;
	rays[pixel].through_power = vec3(1, 1, 1);
	rays[pixel].refract.count = 0;
	rays[pixel].active = true;
	hits[pixel].id = pixel;
}
