/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_light_outline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:42:23 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/16 01:42:25 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define LIGHT_SIZE 40

void	rasterize_light_outline(t_img_data *img, t_light *light,
	t_camera *camera)
{
	t_vec2i		proj;
	t_rgb_int	color;

	color = rgb_int(light->rgb.x * 255, light->rgb.y * 255, light->rgb.z * 255);
	proj = project_point(&light->pos, camera, img);
	if (proj.x == -1)
		return ;
	draw_circle(img, proj, LIGHT_SIZE - 15, color);
	draw_circle(img, proj, LIGHT_SIZE, color);
}
