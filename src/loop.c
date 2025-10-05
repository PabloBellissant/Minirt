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

static inline void  rewind_offsets_x(t_camera *cam, int force)
{
	cam->x_offset = vec3_sub(cam->x_offset, vec3_scale(cam->pixel_delta_u, force));
}


static inline void	compute_offsets_x(t_camera *cam, int force)
{
	cam->x_offset =	vec3_add(cam->x_offset, vec3_scale(cam->pixel_delta_u, force));
}

static inline void	compute_offsets_y(t_camera *cam, int force)
{
	cam->y_offset =	vec3_add(cam->y_offset, vec3_scale(cam->pixel_delta_v, force));
}

static void	clear_old_screen(t_img_data *img, t_bound *bound)
{
	int	i;

	i = bound->top;
	while (i < bound->down + 1)
	{
		ft_fbzero(img->addr + (WIDTH * i + bound->left), (bound->right - bound->left + 1) * 4);
		++i;
	}
	i = 0;
	while (i < 25) // clear fps peut mieux faire mdr
	{
		ft_fbzero(img->addr + (WIDTH * i), 70 * 4);
		++i;
	}
}

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
	cam->x_offset =	vec3_scale(cam->pixel_delta_u, start.x);
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
			color[0] = ray_path(&ray, &data->scene, &hit);
			temp_vec[0] = cam->x_offset;
			cam->x_offset = vec3_add(cam->x_offset, vec3_scale(cam->pixel_delta_u, 0.5f));
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[1] = ray_path(&ray, &data->scene, &hit);
			temp_vec[1] = cam->y_offset;
			cam->y_offset = vec3_add(cam->y_offset, vec3_scale(cam->pixel_delta_v, 0.5f));
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[2] = ray_path(&ray, &data->scene, &hit);
			cam->x_offset = temp_vec[0];
			recalc_camera(cam);
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ray.pos = cam->pos;
			color[3] = ray_path(&ray, &data->scene, &hit);
			cam->y_offset = temp_vec[1];
			recalc_camera(cam);
			ft_mlx_pixel_put(img, (t_vec2i) {{start.x, start.y}}, mix_color(color).rgb);
			cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
			++start.y;
		}
		start.y -= size.y;
		cam->y_offset =	vec3_scale(cam->pixel_delta_v, start.y);
		cam->x_offset = vec3_add(cam->x_offset, cam->pixel_delta_u);
		++start.x;
	}
}
# define SUPERSAMPLING_MIN 5

void	draw_zone(t_img_data *img, t_vec2i start, t_vec2i end, t_data *data)
{
	int			color;
	t_ray		ray;
	t_object	*corners[5];
	t_camera	*cam;
	t_vec2i		size;

	size.x = end.x - start.x;
	size.y = end.y - start.y;
	cam = &data->scene.camera;
	cam->x_offset = vec3_scale(cam->pixel_delta_u, start.x);
	cam->y_offset = vec3_scale(cam->pixel_delta_v, start.y);
	recalc_camera(cam);
	ray.pos = cam->pos;
	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	ray_path(&ray, &data->scene, &corners[0]);

	compute_offsets_y(cam, size.y);
	recalc_camera_y(cam);
	ray.pos = cam->pos;
	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	ray_path(&ray, &data->scene, &corners[2]);

	compute_offsets_x(cam, size.x);
	recalc_camera(cam);
	ray.pos = cam->pos;
	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	ray_path(&ray, &data->scene, &corners[3]);

	cam->y_offset = vec3_scale(cam->pixel_delta_v, start.y);
	recalc_camera_y(cam);
	ray.pos = cam->pos;
	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	ray_path(&ray, &data->scene, &corners[1]);

	rewind_offsets_x(cam, size.x / 2);
	compute_offsets_y(cam, size.y / 2);
	recalc_camera(cam);
	ray.pos = cam->pos;
	ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
	ray_path(&ray, &data->scene, &corners[4]);
	cam->y_offset = vec3_scale(cam->pixel_delta_v, start.y);

	if (!(corners[0] == corners[3] && corners[1] == corners[2] && corners[1] == corners[3] && corners[3] == corners[4]))
	{
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, start.x);
		if (size.x <= SUPERSAMPLING_MIN || size.y <= SUPERSAMPLING_MIN)
		{
			sub_draw(img, start, end, data);
		}
		else
		{
			size.x = end.x - start.x;
			draw_zone(img, start, (t_vec2i) {{end.x - size.x / 2, end.y - size.y / 2}}, data);
			draw_zone(img, (t_vec2i) {{start.x + size.x / 2, start.y}}, (t_vec2i) {{end.x, end.y - size.y / 2}}, data);
			draw_zone(img, (t_vec2i) {{start.x + size.x / 2, start.y + size.y / 2}}, end, data);
			draw_zone(img, (t_vec2i) {{start.x, start.y + size.y / 2}}, (t_vec2i) {{end.x - size.x / 2, end.y}}, data);
		}
	}
	else if (corners[3] != NULL)
	{
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, start.x);
		while (start.x < end.x)
		{
			cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
			while (start.y < end.y)
			{
				recalc_camera_y(cam);
				ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
				ray.pos = cam->pos;
				color = fake_path(&ray, &data->scene, corners[3]).rgb;
				ft_mlx_pixel_put(img, (t_vec2i) {{start.x, start.y}}, color);
				cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
				++start.y;
			}
			start.y -= size.y;
			cam->y_offset =	vec3_scale(cam->pixel_delta_v, start.y);
			cam->x_offset = vec3_add(cam->x_offset, cam->pixel_delta_u);
			++start.x;
		}
	}
	else
		cam->x_offset = vec3_scale(cam->pixel_delta_u, size.x);
}

void	normal_draw(t_img_data *img, t_vec2i pixel, t_camera *cam, t_data *data)
{
	t_ray		ray;
	t_object	*obj;

	pixel.x = data->scene.bvh.bound.left;
	while (pixel.x < data->scene.bvh.bound.right)
	{
		pixel.y = data->scene.bvh.bound.top;
		cam->y_offset =	vec3_scale(cam->pixel_delta_v, pixel.y);
		cam->pixel_center_x = vec3_add(cam->pixel00_loc, cam->x_offset);
		while (pixel.y < data->scene.bvh.bound.down)
		{
			recalc_camera_y(cam);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ft_mlx_pixel_put(img, pixel,
				ray_path(&ray, &data->scene, &obj).rgb);
			cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
			++pixel.y;
		}
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, pixel.x);
		++pixel.x;
	}
}

t_vec2i	get_obj_rasterize_size(t_object *obj, t_camera *cam)
{
	if (obj->type == SPHERE)
	{
		// Calculate vector from camera to sphere center
        t_vec3 cam_to_sphere = vec3_sub(obj->sphere.pos, cam->pos);

        // Calculate distance from camera to sphere center
        float distance = sqrt(vec3_dot(cam_to_sphere, cam_to_sphere)) * 2;

        float cam_z = vec3_dot(cam_to_sphere, cam->camera_forward);
        if (cam_z > 0 && distance > obj->sphere.diameter)
            return ((t_vec2i) {{WIDTH, HEIGHT}});
        float cam_x = vec3_dot(cam_to_sphere, cam->camera_right);
        float cam_y = vec3_dot(cam_to_sphere, cam->camera_up);

        float projected_radius = obj->sphere.diameter * cam->focal_length / (-cam_z);  // Negative because Z is reversed

        if (cam_z < 0) // Only check if in front of camera (negative Z for reversed system)
        {
            float screen_x = cam_x * cam->focal_length / (-cam_z);  // Negative Z
            float screen_y = cam_y * cam->focal_length / (-cam_z);  // Negative Z

            // Check if sphere is outside view frustum
            if (screen_x + projected_radius < -cam->viewport_width / 2.0f ||
                screen_x - projected_radius > cam->viewport_width / 2.0f ||
                screen_y + projected_radius < -cam->viewport_height / 2.0f ||
                screen_y - projected_radius > cam->viewport_height / 2.0f)
                return ((t_vec2i) {{WIDTH, HEIGHT}});  // Not visible
        }

        // Calculate the angular size of the sphere
        float angular_radius = asin(obj->sphere.diameter / distance);

        // Convert angular size to viewport coordinates
        float viewport_radius_y = angular_radius * cam->viewport_height / (2.0f * tan(cam->theta / 2.0f));
        float viewport_radius_x = viewport_radius_y;  // Assuming square pixels

        // Convert viewport coordinates to pixel coordinates
        int pixel_radius_x = (int)(viewport_radius_x * WIDTH / cam->viewport_width) * 4;
        int pixel_radius_y = (int)(viewport_radius_y * HEIGHT / cam->viewport_height) * 4;
        // Return the bounding box size (diameter in pixels)
        return ((t_vec2i) {{pixel_radius_x - 1, pixel_radius_y - 1}});
	}
	else if (obj->type == TRIANGLE)
	{
		// Project all three triangle vertices positions into camera space (view space)
		t_vec3 p0_cam = vec3_sub(obj->triangle.p0.pos, cam->pos);
		t_vec3 p1_cam = vec3_sub(obj->triangle.p1.pos, cam->pos);
		t_vec3 p2_cam = vec3_sub(obj->triangle.p2.pos, cam->pos);

		// Calculate dot products with camera axis vectors
		float p0_z = vec3_dot(p0_cam, cam->camera_forward);
		float p1_z = vec3_dot(p1_cam, cam->camera_forward);
		float p2_z = vec3_dot(p2_cam, cam->camera_forward);

		// If all points are behind camera (z > 0 in your system), return screen max
		if (p0_z > 0 && p1_z > 0 && p2_z > 0)
			return (t_vec2i){{WIDTH, HEIGHT}};

		// Project points to screen plane (using focal length and reversed z)
		float p0_x = vec3_dot(p0_cam, cam->camera_right) * cam->focal_length / (-p0_z);
		float p1_x = vec3_dot(p1_cam, cam->camera_right) * cam->focal_length / (-p1_z);
		float p2_x = vec3_dot(p2_cam, cam->camera_right) * cam->focal_length / (-p2_z);

		float p0_y = vec3_dot(p0_cam, cam->camera_up) * cam->focal_length / (-p0_z);
		float p1_y = vec3_dot(p1_cam, cam->camera_up) * cam->focal_length / (-p1_z);
		float p2_y = vec3_dot(p2_cam, cam->camera_up) * cam->focal_length / (-p2_z);

		// Find bounding rectangle in viewport coordinates
		float min_x = fminf(fminf(p0_x, p1_x), p2_x);
		float max_x = fmaxf(fmaxf(p0_x, p1_x), p2_x);
		float min_y = fminf(fminf(p0_y, p1_y), p2_y);
		float max_y = fmaxf(fmaxf(p0_y, p1_y), p2_y);

		// Convert viewport size to pixel size
		int pixel_width = (int)((max_x - min_x) * WIDTH / cam->viewport_width) * 4;
		int pixel_height = (int)((max_y - min_y) * HEIGHT / cam->viewport_height) * 4;

		// Clamp minimal size to 1 or 0 if behind view
		if (pixel_width < 1) pixel_width = 1;
		if (pixel_height < 1) pixel_height = 1;

		return (t_vec2i){{pixel_width, pixel_height}};
	}

	return ((t_vec2i) {{WIDTH, HEIGHT}});
}

void	set_shortest_object(t_vector *objects, t_camera *cam, int *x, int *y)
{
	t_object	*obj;
	size_t		i;
	t_vec2i		temp;

	obj = objects->data;
	*x = WIDTH;
	*y = HEIGHT;
	i = 0;
	while (i < objects->num_elements)
	{
		if (obj[i].type != PLANE && obj[i].type != LIGHT)
		{
			temp = get_obj_rasterize_size(&obj[i], cam);
			if (temp.x < *x)
				*x = temp.x;
			if (temp.y < *y)
				*y = temp.y;
		}
		++i;
	}
}

static int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	compute(t_data *data)
{
	t_camera	*cam;
	t_scene		*scene;
	t_vec2i		pixel;

	scene = &data->scene;
	cam = &data->scene.camera;
	fill_camera(cam);
	if (scene->plane_count == 0)
	{
		clear_old_screen(&data->mlx->img, &scene->bvh.bound);
		calc_bvh_bound(&data->scene.camera, &scene->bvh.bound, &data->scene.bvh, scene->bvh.bvh_mode);
	}
	else
		scene->bvh.bound = (t_bound) {.right = WIDTH, .down = HEIGHT};
	set_shortest_object(&scene->objects, cam, &data->params.supersampling_x, &data->params.supersampling_y);
	if (data->params.supersampling_x <= 3 || data->params.supersampling_y <= 3)
	{
		data->params.supersampling_x = 1;
		data->params.supersampling_y = 1;
	}
	if (data->params.supersampling_x > 74 || data->params.supersampling_y > 74)
	{
		data->params.supersampling_x = 74;
		data->params.supersampling_y = 74;
	}
	pixel.y = scene->bvh.bound.top;
	cam->y_offset = vec3_scale(cam->pixel_delta_v, pixel.y);
	if (data->params.supersampling_x == 1)
	{
		normal_draw(&data->mlx->img, pixel, cam, data);
	}
	else
	{
		while (pixel.y < scene->bvh.bound.down)
		{
			pixel.x = scene->bvh.bound.left;
			cam->x_offset =	vec3_scale(cam->pixel_delta_u, pixel.x);
			while (pixel.x < scene->bvh.bound.right)
			{
				draw_zone(&data->mlx->img, pixel,
					(t_vec2i) {{imin(pixel.x + data->params.supersampling_x, scene->bvh.bound.right), imin(pixel.y + data->params.supersampling_y, scene->bvh.bound.down)}}, data);
				pixel.x += data->params.supersampling_x;
			}
			compute_offsets_y(cam, data->params.supersampling_y);
			pixel.y += data->params.supersampling_y;
		}
	}
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(scene->bvh.bvh, &data->params, scene->bvh.sphere_bvh->depth, data);
	if (data->params.bound_debug)
		draw_bound(&scene->bvh.bound, &data->mlx->img);
	if (data->params.supersampling_debug)
		draw_supersampling(&scene->bvh.bound, (t_vec2i) {{data->params.supersampling_x, data->params.supersampling_y}}, &data->mlx->img);
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
void	draw_text(t_text *text);

// 84 fps no multi threading
// maximum theorique : 1680 fps PTDR
// ntm vrai objectif : 800fps
// et on as :
int	loop(t_data *data)
{
	update_fps(data);
	handle_camera_move(data,&data->scene.camera, data->keys);
	compute(data);
	draw_text(data->font_env->fps);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	return (0);
}
