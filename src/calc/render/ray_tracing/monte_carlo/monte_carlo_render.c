/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monte_carlo_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:10:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/20 21:10:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "render.h"

bool		cam_has_moved(t_camera *camera);
static void	handle_start(t_buffers *bu, t_img_data *img,
				t_camera *cam, int *sample);

void	monte_carlo_render(t_data *data, t_img_data *img)
{
	t_buffers	bu;
	static int	sample = 0;

	bu = data->buffers;
	handle_start(&bu, img, &data->scene.camera, &sample);
	while (bu.hits_count > 0)
	{
		intersect_loop(bu.rays, bu.hits, &data->scene, bu.hits_count);
		bu.hits_count = compact_hits_inplace(bu.hits, bu.hits_count);
		path_sample_materials_loop(&bu, data->scene.texture.data,
			data->scene.mat.data, bu.hits_count);
		if (data->params.normal_debug)
			normal_debug_loop(&bu, bu.hits_count);
		else
			path_shade_loop(&bu, &data->scene, bu.hits_count);
		draw_skybox_loop(bu, data->scene.skybox_tex, data->scene.texture.data,
			bu.hits_count);
		bu.hits_count = compact_hits_inplace(bu.hits, HEIGHT * WIDTH);
	}
	accu_screen_loop(bu, sample, img);
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(data->scene.bvh.bvh, &data->params,
			data->scene.bvh.sphere_bvh->depth, data);
}

static void	handle_start(t_buffers *bu, t_img_data *img,
				t_camera *cam, int *sample)
{
	if (cam_has_moved(cam))
	{
		*sample = 0;
		ft_bzero(bu->accu, sizeof(t_vec3) * img->width * img->height);
	}
	ft_dprintf(1, "Sample count: %d\n", *sample);
	if (*sample == 0)
		fill_camera(cam, img);
	cast_ray_loop(cam, *bu, 1, img);
	bu->hits_count = img->width * img->height;
	++*sample;
}
