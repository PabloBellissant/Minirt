/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outline_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:16:06 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/15 23:20:07 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		fill_camera(t_camera *cam);
static void	clear_old_screen(t_img_data *img);
static void	rasterize_lights(t_img_data *img, t_vector lights, t_camera *cam);
static void	rasterize_objects(t_img_data *img, t_vector objects, t_camera *cam);

void	outline_render(t_data *data)
{
	t_camera	*cam;
	t_scene		*scene;
	t_img_data	*img;

	scene = &data->scene;
	cam = &scene->camera;
	img = &data->mlx->img;
	fill_camera(cam);
	clear_old_screen(img);
	rasterize_objects(img, scene->objects, cam);
	rasterize_lights(img, scene->lights, cam);
	if (data->params.bvh_debug && data->scene.bvh.bvh)
	{
		rasterize_bvh(scene->bvh.bvh, &data->params,
			scene->bvh.sphere_bvh->depth, data);
	}
}

static void	rasterize_lights(t_img_data *img, t_vector lights, t_camera *cam)
{
	size_t		i;
	t_object	*obj;

	obj = lights.data;
	i = 0;
	while (i < lights.num_elements)
	{
		rasterize_light_outline(img, &obj[i].light, cam);
		++i;
	}
}

static void	rasterize_objects(t_img_data *img, t_vector objects, t_camera *cam)
{
	size_t		i;
	t_object	*obj;

	obj = objects.data;
	i = 0;
	while (i < objects.num_elements)
	{
		rasterize_outline_object(img, &obj[i], cam, rgb_int(255, 255, 255));
		++i;
	}
}

static void	clear_old_screen(t_img_data *img)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		ft_fbzero(img->addr + (WIDTH * i), WIDTH * 4);
		++i;
	}
}
