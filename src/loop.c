/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/22 20:15:45 by pabellis         ###   ########.fr       */
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

int	optimal_radius(int frame_time_ms, int pixel_size)
{
	float	target_time;

	target_time = 1000000.0f / TARGET_FPS;
	return ((int)(pixel_size * sqrtf((float)frame_time_ms / target_time)));
}

int	get_smooth_size(t_camera *cam, t_data *data)
{
	int			low_quality_frame_time;
	int			optimal;
	int			min;

	low_quality_frame_time = (int) simulate_low_quality(cam, data);
	optimal = optimal_radius(low_quality_frame_time, LOW_QUALITY_SIMULATION);
	min = MIN_QUALITY;
	return (imin(min, optimal));
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

void	cast_rays(t_camera *cam, t_ray *buffer, int pixel);
void	cast_ray_loop(t_camera *cam, t_ray *buffer)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT * SUB_PIXEL_QUANTITY)
	{
		cast_rays(cam, buffer, i);
		++i;
	}
}

void	intersect_scene(t_ray *rays, t_hit *hits, t_scene *scene, int pixel);
void	intersect_loop(t_ray *rays, t_hit *hits, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT * SUB_PIXEL_QUANTITY)
	{
		intersect_scene(rays, hits, scene, i);
		++i;
	}
}

void	draw_skybox(int pixel, t_buffers bu, int texture_id, t_texture *texture);
void	draw_skybox_loop(t_buffers bu, int texture_id, t_texture *texture, int size)
{
	int	i;

	i = size;
	while (i < (WIDTH * HEIGHT * SUB_PIXEL_QUANTITY))
	{
		draw_skybox(i, bu, texture_id, texture);
		++i;
	}
}

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

void	sample_materials(t_hit *hits, int pixel, t_texture *tex, t_mat *mat);
void	sample_materials_loop(t_hit *hits, t_texture *tex, t_mat *mat, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sample_materials(hits, i, tex, mat);
		++i;
	}
}

void	test_loop(t_hit *hits, t_img_data *img, int count)
{
	int			pixel;
	int			x;
	int			y;

	pixel = 0;
	while (pixel < count)
	{
		x = hits[pixel].id % WIDTH;
		y = hits[pixel].id / WIDTH;
		ft_mlx_pixel_put(img, vec2i(x, y), rgb_ftoi(hits[pixel].hit_rgb));
		++pixel;
	}
}

void	intersect_shadow(t_hit *hits, t_shadow_result *results, t_scene *scene, int pixel);
void	intersect_shadow_loop(t_hit *hits, t_shadow_result *results, t_scene *scene, int count)
{
	int			pixel;

	pixel = 0;
	while (pixel < count)
	{
		intersect_shadow(hits, results, scene, pixel);
		++pixel;
	}
}

void	shade(t_buffers *buffers, int pixel, t_scene *scene, t_data *data);
void	shade_loop(t_buffers *buffers, t_scene *scene, t_data *data, int count)
{
	int			pixel;

	pixel = 0;
	while (pixel < count)
	{
		shade(buffers, pixel, scene, data);
		++pixel;
	}
}

void	ray_tracing_render(t_data *data)
{
	t_camera	*cam;
	static int	pixel_size;
	static int	actual_pixel;

	if (data->params.exporting)
	{
		export_to_ppm(data, data->mlx);
		return ;
	}
	cam = &data->scene.camera;
	fill_camera(cam);
	if ((!cam_has_moved(&data->scene.camera) && data->params.quality_render))
	{
		if (actual_pixel == pixel_size * pixel_size)
			actual_pixel = 0;
		draw_individual(&data->mlx->img, cam, data, pixel_size, actual_pixel);
		++actual_pixel;
	}
	else
	{
		// cast_ray_loop(cam, data->buffers.rays);
		// intersect_loop(data->buffers.rays, data->buffers.hits, &data->scene);
		// data->buffers.hits_count = compact_hits_inplace(data->buffers.hits, HEIGHT * WIDTH * SUB_PIXEL_QUANTITY);
		// draw_skybox_loop(data->buffers, data->scene.skybox_tex, data->scene.texture.data, data->buffers.hits_count);
		// sample_materials_loop(data->buffers.hits, data->scene.texture.data, data->scene.mat.data, data->buffers.hits_count);
		// intersect_shadow_loop(data->buffers.hits, data->buffers.shadows_result, &data->scene, data->buffers.hits_count);
		// shade_loop(&data->buffers, &data->scene, data, data->buffers.hits_count);

		// actual_pixel = 0;
		pixel_size = get_smooth_size(cam, data);
		draw(&data->mlx->img, cam, data, pixel_size);
	}
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(data->scene.bvh.bvh, &data->params, data->scene.bvh.sphere_bvh->depth, data);
}

int	loop(t_data *data)
{
	static void (*render_func[])(t_data *)
		= {wireframe_render, ray_tracing_render};
	if (data->params.render_mode == 1)
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
