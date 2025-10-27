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

static inline void	recalc_camera(t_camera *cam)
{
	cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center_x, cam->y_offset);
}

// static inline void  rewind_offsets_x(t_camera *cam, int force)
// {
// 	cam->x_offset = vec3_sub(cam->x_offset,
// 		vec3_scale(cam->pixel_delta_u, (float)force));
// }
//
//
// static inline void	compute_offsets_x(t_camera *cam, int force)
// {
// 	cam->x_offset =	vec3_add(cam->x_offset,
// 		vec3_scale(cam->pixel_delta_u, (float)force));
// }
//
// static inline void	compute_offsets_y(t_camera *cam, int force)
// {
// 	cam->y_offset =	vec3_add(cam->y_offset,
// 		vec3_scale(cam->pixel_delta_v, (float)force));
// }

// static void	clear_old_screen(t_img_data *img, t_bound *bound)
// {
// 	int	i;
//
// 	i = bound->top;
// 	while (i < bound->down + 1)
// 	{
// 		ft_fbzero(img->addr + (WIDTH * i + bound->left), (size_t)(bound->right - bound->left + 1) * 4);
// 		++i;
// 	}
// 	i = 0;
// 	while (i < 25) // clear fps peut mieux faire mdr
// 	{
// 		ft_fbzero(img->addr + (WIDTH * i), 70 * 4);
// 		++i;
// 	}
// }

#include "render.h"

//
// #include "threading.h"
//
// int	threadify(t_to_task *data)
// {
// 	t_vec2i	pixel;
// 	t_ray	ray = data->ray;
// 	t_scene	*scene;
//
// 	scene = &data->data->scene;
// 	pixel.x = scene->bvh.bound.left;
// 	pixel.y = data->y;
// 	data->cam.x_offset = vec3_scale(data->cam.pixel_delta_u, pixel.x + 1);
// 	while (pixel.x < scene->bvh.bound.right)
// 	{
// 		compute_offsets_x(&data->cam);
// 		ray.pos = data->cam.pos;
// 		ray.dir = vec3_normalize(vec3_sub(data->cam.pixel_center, data->cam.pos));
// 		ft_mlx_pixel_put(&data->data->mlx->img, pixel,
// 			ray_path(&ray, scene).rgb);
// 		++pixel.x;
// 	}
// 	return (0);
// }

t_rgb_int	fake_path(t_ray *ray, t_scene *scene, t_object *hit_object);

t_rgb_int	mix_color(t_rgb_int color[4])
{
	t_rgb_int	result;
	uint32_t	sum_r;
	uint32_t	sum_g;
	uint32_t	sum_b;
	int			i;

	sum_r = 0;
	sum_g = 0;
	sum_b = 0;
	i = 0;
	while (i < 4)
	{
		sum_r += color[i].r;
		sum_g += color[i].g;
		sum_b += color[i].b;
		++i;
	}
	result.r = (uint8_t)((sum_r + 2) >> 2);
	result.g = (uint8_t)((sum_g + 2) >> 2);
	result.b = (uint8_t)((sum_b + 2) >> 2);
	return result;
}

void	sub_draw(t_img_data *img, t_vec2i start, t_vec2i end, t_data *data)
{
	t_rgb_int	color[4];
	t_ray		ray;
	t_object	*hit;
	t_vec3		temp_vec[2];
	t_camera	*cam;
	t_vec2i		size;

	size.x = end.x - start.x;
	size.y = end.y - start.y;
	cam = &data->scene.camera;
	cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)start.x);
	cam->x_offset = vec3_sub(cam->x_offset, vec3_scale(cam->pixel_delta_u, 0.25f));
	cam->y_offset = vec3_sub(cam->y_offset, vec3_scale(cam->pixel_delta_v, 0.25f));
	while (start.x < end.x)
	{
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (start.y < end.y)
		{
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[0] = ray_path(&ray, data, &hit);
			temp_vec[0] = cam->x_offset;
			cam->x_offset = vec3_add(cam->x_offset, vec3_scale(cam->pixel_delta_u, 0.5f));
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[1] = ray_path(&ray, data, &hit);
			temp_vec[1] = cam->y_offset;
			cam->y_offset = vec3_add(cam->y_offset, vec3_scale(cam->pixel_delta_v, 0.5f));
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[2] = ray_path(&ray, data, &hit);
			cam->x_offset = temp_vec[0];
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[3] = ray_path(&ray, data, &hit);
			cam->y_offset = temp_vec[1];
			recalc_camera(cam);
			ft_mlx_pixel_put(img, (t_vec2i) {{start.x, start.y}}, (int)mix_color(color).rgb);
			cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
			++start.y;
		}
		start.y -= size.y;
		cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)start.y);
		cam->x_offset = vec3_add(cam->x_offset, cam->pixel_delta_u);
		++start.x;
	}
}
# define SUPERSAMPLING_MIN 5
t_rgb_int	draw_skybox(t_scene *scene, t_vec3 *dir);
//
// void	draw_zone(t_img_data *img, t_vec2i start, t_vec2i end, t_data *data)
// {
// 	int			color;
// 	t_ray		ray;
// 	t_object	*corners[5];
// 	t_camera	*cam;
// 	t_vec2i		size;
//
// 	size.x = end.x - start.x;
// 	size.y = end.y - start.y;
// 	cam = &data->scene.camera;
// 	cam->x_offset = vec3_scale(cam->pixel_delta_u, (float)start.x);
// 	cam->y_offset = vec3_scale(cam->pixel_delta_v, (float)start.y);
// 	recalc_camera(cam);
// 	ray.pos = cam->pos;
// 	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 	ray_path(&ray, data, &corners[0]);
//
// 	compute_offsets_y(cam, size.y);
// 	recalc_camera_y(cam);
// 	ray.pos = cam->pos;
// 	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 	ray_path(&ray, data, &corners[2]);
//
// 	compute_offsets_x(cam, size.x);
// 	recalc_camera(cam);
// 	ray.pos = cam->pos;
// 	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 	ray_path(&ray, data, &corners[3]);
//
// 	cam->y_offset = vec3_scale(cam->pixel_delta_v, (float)start.y);
// 	recalc_camera_y(cam);
// 	ray.pos = cam->pos;
// 	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 	ray_path(&ray, data, &corners[1]);
//
// 	rewind_offsets_x(cam, size.x / 2);
// 	compute_offsets_y(cam, size.y / 2);
// 	recalc_camera(cam);
// 	ray.pos = cam->pos;
// 	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 	ray_path(&ray, data, &corners[4]);
// 	cam->y_offset = vec3_scale(cam->pixel_delta_v, (float)start.y);
//
// 	if (!(corners[0] == corners[3] && corners[1] == corners[2] && corners[1] == corners[3] && corners[3] == corners[4]))
// 	{
// 		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)start.x);
// 		if (size.x <= SUPERSAMPLING_MIN || size.y <= SUPERSAMPLING_MIN)
// 		{
// 			sub_draw(img, start, end, data);
// 		}
// 		else
// 		{
// 			size.x = end.x - start.x;
// 			draw_zone(img, start, (t_vec2i) {{end.x - size.x / 2, end.y - size.y / 2}}, data);
// 			draw_zone(img, (t_vec2i) {{start.x + size.x / 2, start.y}}, (t_vec2i) {{end.x, end.y - size.y / 2}}, data);
// 			draw_zone(img, (t_vec2i) {{start.x + size.x / 2, start.y + size.y / 2}}, end, data);
// 			draw_zone(img, (t_vec2i) {{start.x, start.y + size.y / 2}}, (t_vec2i) {{end.x - size.x / 2, end.y}}, data);
// 		}
// 	}
// 	else
// 	{
// 		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)start.x);
// 		while (start.x < end.x)
// 		{
// 			cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
// 			while (start.y < end.y)
// 			{
// 				recalc_camera_y(cam);
// 				ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
// 				ray.pos = cam->pos;
// 				if (corners[3] != NULL)
// 					color = (int)fake_path(&ray, &data->scene, corners[3]).rgb;
// 				else
// 					color = (int)draw_skybox(&data->scene, &ray.dir).rgb;
// 				ft_mlx_pixel_put(img, (t_vec2i) {{start.x, start.y}}, color);
// 				cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
// 				++start.y;
// 			}
// 			start.y -= size.y;
// 			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)start.y);
// 			cam->x_offset = vec3_add(cam->x_offset, cam->pixel_delta_u);
// 			++start.x;
// 		}
// 	}
// }


int	get_subsampling(t_vec2 pixel, t_camera *cam, int ray_count, t_data *data)
{
	t_ray		ray;
	t_object	*obj;
	t_rgb		color;
	t_rgb_int	int_color;
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
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			int_color = ray_path(&ray, data, &obj);
			color = rgb_add(color, rgb_itof(int_color));
			sub_pixel.y += 1.0f / (float)ray_count;
		}
		sub_pixel.x += 1.0f / (float)ray_count;
	}
	color = rgb_div_scalar(color, (float)ray_count * (float)ray_count);
	return ((int)rgb_ftoi(color).rgb);
}

#define RAY_COUNT 2

void	subsampling_draw(t_img_data *img, t_camera *cam, t_data *data)
{
	t_ray		ray;
	int			color;
	t_vec2i		pixel;

	pixel.x = data->scene.bvh.bound.left;
	while (pixel.x < data->scene.bvh.bound.right)
	{
		pixel.y = data->scene.bvh.bound.top;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel.x);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < data->scene.bvh.bound.down)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)pixel.y);
			recalc_camera_y(cam);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			color = get_subsampling(vec2((float)pixel.x, (float)pixel.y), cam, RAY_COUNT, data);
			ft_mlx_pixel_put(img, pixel, color);
			pixel.y += 1;
		}
		pixel.x += 1;
	}
}

void	draw_zone(t_img_data *img, t_vec2i pos, int color, int size)
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

	if (pixel_size < 1)
	{
		subsampling_draw(img, cam, data);
		return ;
	}
	pixel.x = data->scene.bvh.bound.left;
	while (pixel.x < data->scene.bvh.bound.right)
	{
		pixel.y = data->scene.bvh.bound.top;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, (float)pixel.x);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < data->scene.bvh.bound.down)
		{
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, (float)pixel.y);
			recalc_camera_y(cam);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			draw_zone(img, pixel, (int)ray_path(&ray, data, &obj).rgb, pixel_size);
			pixel.y += pixel_size;
		}
		pixel.x += pixel_size;
	}
}

#define LOW_QUALITY_SIMULATION 75

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
			ray.pos = cam->pos;
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

bool	is_near_value(int v1, int v2, int distance)
{
	if (v1 - distance <= v2 && v1 + distance >= v2)
		return (true);
	return (false);
}

int	get_smooth_size(t_camera *cam, t_data *data)
{
	int			low_quality_frame_time;
	int			optimal;
	int			min;
	static int	old_quality = -1;

	min = 50;
	low_quality_frame_time = (int) simulate_low_quality(cam, data);
	if (!data->params.quality_render)
		optimal = optimal_radius(low_quality_frame_time, LOW_QUALITY_SIMULATION);
	else
		optimal = 1;
	min = MIN_QUALITY;
	if (is_near_value(optimal, old_quality, 2))
		return (imin(min, old_quality));
	old_quality = optimal;
	return (imin(min, optimal));
}

void	ray_tracing_render(t_data *data)
{
	t_camera	*cam;
	t_scene		*scene;
	int			pixel_size;

	scene = &data->scene;
	cam = &data->scene.camera;
	fill_camera(cam);
	pixel_size = get_smooth_size(cam, data);
	scene->bvh.bound = (t_bound) {.right = WIDTH, .down = HEIGHT};
	draw(&data->mlx->img, cam, data, pixel_size);
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(scene->bvh.bvh, &data->params, scene->bvh.sphere_bvh->depth, data);
	if (data->params.bound_debug)
		draw_bound(&scene->bvh.bound, &data->mlx->img);
}

//
// #include <pthread.h>
// void	compute(t_data *data)
// {
// 	t_scene		*scene;
// 	int			y;
//
// 	scene = &data->scene;
// 	fill_camera(&data->scene.camera);
// 	if (scene->plane_count == 0)
// 	{
// 		clear_old_screen(&data->mlx->img, &scene->bvh.bound);
// 		calc_bvh_bound(&data->scene.camera, &scene->bvh.bound, &data->scene.bvh, scene->bvh.bvh_mode);
// 	}
// 	else
// 		scene->bvh.bound = (t_bound) {.right = WIDTH, .down = HEIGHT};
// 	y = scene->bvh.bound.top;
// 	data->scene.camera.y_offset = vec3_scale(data->scene.camera.pixel_delta_v, y + 1);
// 	while (y < scene->bvh.bound.down)
// 	{
// 		compute_offsets_y(&data->scene.camera);
// 		data->to_task[y].y = y;
// 		data->to_task[y].cam = data->scene.camera;
// 		data->to_task[y].data = data;
// 		data->task[y].f = (int (*)(void *))&threadify;
// 		data->task[y].data = &(data->to_task[y]);
// 		enqueue(&(data->task[y]), data->queue);
// 		++y;
// 	}
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->queue->mutex_queue);
// 		if (data->queue->len == 0)
// 		{
// 			pthread_mutex_unlock(&data->queue->mutex_queue);
// 			break;
// 		}
// 		pthread_mutex_unlock(&data->queue->mutex_queue);
// 	}
// 	if (data->params.bvh_debug && data->scene.bvh.bvh)
// 		rasterize_bvh(scene->bvh.bvh, &data->params, scene->bvh.sphere_bvh->depth, data);
// 	if (data->params.bound_debug)
// 		draw_bound(&scene->bvh.bound, &data->mlx->img);
// }

void	update_fps(t_data *data);

// 84 fps no multi threading
// maximum theorique : 1680 fps PTDR
// ntm vrai objectif : 800fps
// et on as :
int	loop(t_data *data)
{
	static void (*render_func[])(t_data *)
		= {wireframe_render, ray_tracing_render};

	update_fps(data);
	handle_camera_move(data, &data->scene.camera, data->keys);
	render_func[data->params.render_mode](data);
	draw_text(data->font_env->fps);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	return (0);
}
