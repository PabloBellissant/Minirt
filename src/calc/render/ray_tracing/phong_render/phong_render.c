/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:10:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/20 21:10:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_camera(t_camera *cam);
void	cast_ray_loop(t_camera *cam, t_ray *buffer, t_hit *hits, int pixel_size);
void	intersect_loop(t_ray *rays, t_hit *hits, t_scene *scene, int count);
void	draw_skybox_loop(t_buffers bu, int texture_id, t_texture *texture, int size);

int compact_hits_inplace(t_hit *buffer, int input_size);

void	sample_colors_loop(t_data *data, t_texture *tex, t_mat *mat, int count);

void	shade_loop(t_buffers *buffers, t_scene *scene, t_data *data, int count);

void	draw_screen_loop(t_ray *rays, unsigned int *addr, int pixel_size);
void	normal_debug_loop(t_buffers *buffers, int count);


void	phong_render(t_data *data)
{
	int			pixel_size;
	t_camera	*cam;

	pixel_size = 1;
	cam = &data->scene.camera;
	fill_camera(cam);
	cast_ray_loop(cam, data->buffers.rays, data->buffers.hits, pixel_size);
	data->buffers.hits_count = HEIGHT * WIDTH;
	
	intersect_loop(data->buffers.rays, data->buffers.hits, &data->scene, data->buffers.hits_count);
	data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, data->buffers.hits_count);
	sample_colors_loop(data, data->scene.texture.data, data->scene.mat.data, data->buffers.hits_count);
	if (data->params.normal_debug)
		normal_debug_loop(&data->buffers, data->buffers.hits_count);
	else	
		shade_loop(&data->buffers, &data->scene, data, data->buffers.hits_count);
	
	draw_screen_loop(data->buffers.rays, data->mlx->img.addr, pixel_size);
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(data->scene.bvh.bvh, &data->params, data->scene.bvh.sphere_bvh->depth, data);
}


