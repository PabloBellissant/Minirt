/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 01:55:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "bvh.h"
#include "vectors.h"
#include "calc.h"
#include "minirt.h"

void	fill_camera(t_camera *cam, t_img_data *img);
void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys);

ssize_t	get_max_frame_time()
{
	return (1000000.0f / TARGET_FPS);	
}

int	get_smooth_size(ssize_t frame_time, int old_quality)
{
	ssize_t		target_time;
	int			min;
	int			optimal;

	target_time = get_max_frame_time();
	if (frame_time * 0.9 < target_time && frame_time * 1.1 > target_time)
		return (old_quality);
	if (frame_time / 2 > target_time)
		optimal = old_quality *= 2;
	else if (frame_time < target_time / 2)
		optimal = old_quality /= 2;
	else if (frame_time > target_time)
		optimal = old_quality + 1;
	else
	 	optimal = old_quality - 1;
	min = MIN_QUALITY;
	return (imax(imin(min, optimal), 1));
}

bool	cam_has_moved(t_camera *camera)
{
	static t_vec3	pos;
	static t_vec3	rot;
	static int		fov;

	if (ft_memcmp(&camera->pos, &pos, sizeof(t_vec3)) != 0
		|| ft_memcmp(&camera->rot, &rot, sizeof(t_vec3)) != 0
		|| fov != camera->fov)
	{
		pos = camera->pos;
		rot = camera->rot;
		fov = camera->fov;
		return (true);
	}
	return (false);
}

void	cast_ray_loop(t_camera *cam, t_buffers bu, int pixel_size, t_img_data *img);
void	intersect_loop(t_ray *rays, t_hit *hits, t_scene *scene, int count);
void	draw_skybox_loop(t_buffers bu, int texture_id, t_texture *texture, int size);

int compact_hits_inplace(t_hit *buffer, int input_size)
{
	int		write_pos;
	int		read_pos;
	t_hit	temp;

	write_pos = 0;
	read_pos = 0;
	while (read_pos < input_size)
	{
		if (buffer[read_pos].hit == true)
		{
			if (write_pos != read_pos)
			{
				temp = buffer[write_pos];
				buffer[write_pos] = buffer[read_pos];
				buffer[read_pos] = temp;
			}
			write_pos++;
		}
		++read_pos;
	}
	return (write_pos);
}

void	sample_materials_loop(t_buffers *buffers, t_texture *tex, t_mat *mat, int count);

void	shade_loop(t_buffers *buffers, t_scene *scene, t_data *data, int count);

void	draw_screen_loop(t_ray *rays, t_img_data *img, int pixel_size);

ssize_t	get_precise_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((ssize_t)time.tv_sec * 1000000L) + (ssize_t)time.tv_usec;
}

void	pbr_render(t_data *data, t_img_data *img)
{
	t_camera	*cam;
	static int	pixel_size = 10;
	// static int	actual_pixel;

	(void) img;
	if (data->params.exporting)
	{
		//export_to_ppm(data, data->mlx);
		return ;
	}
	cam = &data->scene.camera;
	fill_camera(cam, img);
// 	if ((!cam_has_moved(&data->scene.camera) && data->params.quality_render))
// 	{
// 		if (actual_pixel == pixel_size * pixel_size)
// 			actual_pixel = 0;
// //		draw_individual(&data->mlx->img, cam, data, pixel_size, actual_pixel);
// 		++actual_pixel;
// 	}
	// else
	{
		ssize_t		start_time;
		
		if (data->params.quality_render)
			pixel_size = 1;
		start_time = get_precise_time();
		cast_ray_loop(cam, data->buffers, pixel_size, img);
		data->buffers.hits_count = img->width * img->height;
		while (data->buffers.hits_count > 0)
		{
			intersect_loop(data->buffers.rays, data->buffers.hits, &data->scene, data->buffers.hits_count);
			data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, data->buffers.hits_count);
			sample_materials_loop(&data->buffers, data->scene.texture.data, data->scene.mat.data, data->buffers.hits_count);
			shade_loop(&data->buffers, &data->scene, data, data->buffers.hits_count);
			draw_skybox_loop(data->buffers, data->scene.skybox_tex, data->scene.texture.data, data->buffers.hits_count);
			data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, img->width * img->height);
		}
		draw_screen_loop(data->buffers.rays, &data->mlx->img, pixel_size);
		// actual_pixel = 0;
		pixel_size = get_smooth_size(get_precise_time() - start_time, pixel_size);
	}
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(data->scene.bvh.bvh, &data->params, data->scene.bvh.sphere_bvh->depth, data); 
}

void	phong_render(t_data *data, t_img_data *img);
void	monte_carlo_render(t_data *data, t_img_data *img);

int	loop(t_data *data)
{
	static void (*render_func[])(t_data *, t_img_data *img)
		= {wireframe_render, phong_render, pbr_render, monte_carlo_render};
	if (data->params.render_mode != 0)
	{
		if (!data->scene.bvh.bvh_pointer)
		{
			data->scene.bvh.bvh_mode = 1;
			if (load_bvh(data->scene.bvh.bvh_mode, &data->scene) == -1)
				return (-1);
			data->params.bvh_depth = data->scene.bvh.aabb_bvh->depth;
		}
	}
	handle_camera_move(data, &data->scene.camera, data->keys);
	render_func[data->params.render_mode](data, &data->mlx->img);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	return (0);
}
