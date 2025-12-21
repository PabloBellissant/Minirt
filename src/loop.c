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

void	fill_camera(t_camera *cam);
void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys);

/*
static inline void	recalc_camera_y(t_camera *cam)
{
	cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
}

#include "render.h"
int	get_subsampling(t_vec2 pixel, t_camera *cam, int ray_count, t_data *data)
{
	t_ray		ray;
	t_object	*obj;
	t_rgb		color;
	t_vec2		sub_pixel;

	color = rgb(0, 0, 0);
	pixel.x -= 0.5f / ray_count;
	pixel.y -= 0.5f / ray_count;
	sub_pixel.x = 0;
	while (sub_pixel.x < 1)
	{
		sub_pixel.y = 0;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, pixel.x + sub_pixel.x);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (sub_pixel.y < 1)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, pixel.y + sub_pixel.y);
			recalc_camera_y(cam);
			ray.origin = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			color = rgb_add(color, ray_path(&ray, data, &obj));
			sub_pixel.y += 1.0f / (float)ray_count;
		}
		sub_pixel.x += 1.0f / (float)ray_count;
	}
	color = rgb_div_scalar(color, (float)ray_count * (float)ray_count);
	return ((int)rgb_ftoi(color).rgb);
}

void	draw_zone(t_img_data *img, t_vec2i pos, t_rgb_int color, int size)
{
	t_vec2i	pixel;

	pixel.x = 0;
	while (pixel.x < size && pixel.x + pos.x < WIDTH)
	{
		pixel.y = 0;
		while (pixel.y < size && pixel.y + pos.y < HEIGHT)
		{
			ft_mlx_pixel_put(img, vec2i_add(pixel, pos), color);
			++pixel.y;
		}
		++pixel.x;
	}
}

void	draw(t_img_data *img, t_camera *cam, t_data *data, int pixel_size)
{
	t_ray		ray;
	t_object	*obj;
	t_vec2i		pixel;

	pixel.x = 0;
	while (pixel.x < img->width)
	{
		pixel.y = 0;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel.x + pixel_size / 2);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < img->height)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)pixel.y + pixel_size / 2);
			recalc_camera_y(cam);
			ray.origin = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			draw_zone(img, pixel, rgb_ftoi(ray_path(&ray, data, &obj)), pixel_size);
			pixel.y += pixel_size;
		}
		pixel.x += pixel_size;
	}
}

void	draw_individual(t_img_data *img, t_camera *cam, t_data *data, int pixel_size, int actual_pixel)
{
	t_rgb_int	color;
	t_vec2i		pixel;

	pixel.x = actual_pixel % pixel_size;
	while (pixel.x < img->width)
	{
		pixel.y = actual_pixel / pixel_size;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel.x);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < img->height)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)pixel.y);
			recalc_camera_y(cam);
			color.rgb = get_subsampling(vec2((float)pixel.x, (float)pixel.y), cam, SUB_PIXEL_QUANTITY, data);
			ft_mlx_pixel_put(img, pixel, color);
			pixel.y += pixel_size;
		}
		pixel.x += pixel_size;
	}
}

#define LOW_QUALITY_SIMULATION 100

ssize_t	get_precise_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((ssize_t)time.tv_sec * 1000000L) + (ssize_t)time.tv_usec;
}


ssize_t	simulate_low_quality(t_camera *cam, t_data *data)
{
	t_ray		ray;
	t_object	*obj;
	t_vec2i		pixel;
	ssize_t		start_time;

	start_time = get_precise_time();
	pixel.x = 0;
	while (pixel.x < WIDTH)
	{
		pixel.y = 0;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel.x);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < HEIGHT)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)pixel.y);
			recalc_camera_y(cam);
			ray.origin = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			(void) ray_path(&ray, data, &obj);
			pixel.y += LOW_QUALITY_SIMULATION;
		}
		pixel.x += LOW_QUALITY_SIMULATION;
	}
	return (get_precise_time() - start_time);
}

*/

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

void	cast_ray_loop(t_camera *cam, t_ray *buffer, t_hit *hits, int pixel_size);
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

void	draw_screen_loop(t_ray *rays, unsigned int *addr, int pixel_size);

ssize_t	get_precise_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((ssize_t)time.tv_sec * 1000000L) + (ssize_t)time.tv_usec;
}

void	pbr_render(t_data *data)
{
	t_camera	*cam;
	static int	pixel_size = 10;
	// static int	actual_pixel;

	if (data->params.exporting)
	{
		//export_to_ppm(data, data->mlx);
		return ;
	}
	cam = &data->scene.camera;
	fill_camera(cam);
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
		cast_ray_loop(cam, data->buffers.rays, data->buffers.hits, pixel_size);
		data->buffers.hits_count = HEIGHT * WIDTH;
		while (data->buffers.hits_count > 0)
		{
			intersect_loop(data->buffers.rays, data->buffers.hits, &data->scene, data->buffers.hits_count);
			data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, data->buffers.hits_count);
			sample_materials_loop(&data->buffers, data->scene.texture.data, data->scene.mat.data, data->buffers.hits_count);
			shade_loop(&data->buffers, &data->scene, data, data->buffers.hits_count);
			draw_skybox_loop(data->buffers, data->scene.skybox_tex, data->scene.texture.data, data->buffers.hits_count);
			data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, HEIGHT * WIDTH);
		}
		draw_screen_loop(data->buffers.rays, data->mlx->img.addr, pixel_size);
		// actual_pixel = 0;
		pixel_size = get_smooth_size(get_precise_time() - start_time, pixel_size);
	}
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(data->scene.bvh.bvh, &data->params, data->scene.bvh.sphere_bvh->depth, data); 
}

void	phong_render(t_data *data);

int	loop(t_data *data)
{
	static void (*render_func[])(t_data *)
		= {wireframe_render, phong_render, pbr_render};
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
	render_func[data->params.render_mode](data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	return (0);
}
