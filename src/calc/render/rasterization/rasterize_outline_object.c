/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_outline_object.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:20:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/15 23:20:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	rasterize_outline_object(t_img_data *img, t_object *object,
	t_camera *camera, t_rgb_int color)
{
	if (object->type == SPHERE)
		rasterize_sphere_outline(&object->sphere, img, camera, color);
	else if (object->type == TRIANGLE)
		rasterize_triangle_outline(img, &object->triangle, color.rgb, camera);
	else if (object->type == PLANE)
		rasterize_plane_outline(img, &object->plane, color.rgb, camera);
	else if (object->type == CYLINDER)
		rasterize_cylinder_outline(img, &object->cylinder, color.rgb, camera);
}
