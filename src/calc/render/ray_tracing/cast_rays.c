/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:05:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 01:56:38 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_inv(t_vec3 vec)
{
	return (vec3(1.0f / vec.x, 1.0f / vec.y, 1.0f / vec.z));
}

void	cast_rays(t_camera *cam, t_buffers bu, int pixel, t_img_data *img)
{
	int	x;
	int	y;

	x = pixel % img->width;
	y = pixel / img->width;
	cam->x_offset = vec3_scale(cam->pixel_delta_u, (float) x);
	cam->y_offset = vec3_scale(cam->pixel_delta_v, (float) y);
	cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
	bu.rays[pixel].origin = cam->pos;
	bu.rays[pixel].dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	bu.rays[pixel].accumulated_color = rgb(0, 0, 0);
	bu.rays[pixel].iteration = 0;
	bu.rays[pixel].through_power = vec3(1, 1, 1);
	bu.rays[pixel].refract.count = 0;
	bu.rays[pixel].active = true;
	bu.hits[pixel].id = pixel;
	bu.rays[pixel].inv_dir = vec3_inv(bu.rays[pixel].dir);
}

void	cast_ray_loop(t_camera *cam, t_buffers bu,
		int pixel_size, t_img_data *img)
{
	t_vec2i	pixel;

	ft_bzero(bu.rays, img->width * img->height * sizeof(t_ray));
	ft_bzero(bu.hits, img->width * img->height * sizeof(t_hit));
	pixel.y = 0;
	while (pixel.y < img->height)
	{
		pixel.x = 0;
		while (pixel.x < img->width)
		{
			cast_rays(cam, bu, (pixel.y * img->width + pixel.x), img);
			pixel.x += pixel_size;
		}
		pixel.y += pixel_size;
	}
}
