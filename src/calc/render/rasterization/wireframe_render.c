/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:16:06 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/12 01:20:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clear_old_screen(t_img_data *img);
static void	rasterize_lights(t_img_data *img, t_vector lights, t_camera *cam);
void		rasterize_objects(t_img_data *img, t_vector objects, t_camera *cam,
				t_rgb_int col);

int	wireframe_render(t_data *data, t_img_data *img)
{
	t_camera	*cam;
	t_scene		*scene;

	scene = &data->scene;
	cam = &scene->camera;
	fill_camera(cam, img);
	clear_old_screen(img);
	rasterize_objects(img, scene->objects, cam, rgb_int(255, 255, 255));
	rasterize_lights(img, scene->light, cam);
	return (0);
}

static void	rasterize_lights(t_img_data *img, t_vector lights, t_camera *cam)
{
	size_t	i;
	t_light	*light;

	light = lights.data;
	i = 0;
	while (i < lights.num_elements)
	{
		rasterize_light_outline(img, &light[i], cam);
		++i;
	}
}

void	rasterize_objects(
			t_img_data *img, t_vector objects, t_camera *cam, t_rgb_int col)
{
	size_t		i;
	t_object	*obj;

	obj = objects.data;
	i = 0;
	while (i < objects.num_elements)
	{
		rasterize_outline_object(img, &obj[i], cam, col);
		++i;
	}
}

static void	clear_old_screen(t_img_data *img)
{
	ft_fbzero(img->pixels, img->width * img->height * 4);
}
