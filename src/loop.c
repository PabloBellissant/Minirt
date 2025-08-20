/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:51:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "vectors.h"
#include "calc.h"
#include "minirt.h"

void	fill_camera(t_camera *cam);
void	handle_camera_move(t_camera *cam, t_keys keys);

static void	frame_gen(void compute(void *), void *data)
{
	static struct timeval	start;
	static struct timeval	stop;
	static size_t			total_time = 0;
	static size_t			generation = 0;
	size_t					frame_time;

	gettimeofday(&start, NULL);
	compute(data);
	gettimeofday(&stop, NULL);
	frame_time = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	total_time += frame_time;
	generation++;
	if (!DEBUG)
		printf("\033[H\033[J");
	printf("[FRAME %zu]\nFrame time:\t%zu μs\n", generation, frame_time);
	printf("Average:\t%zu μs\n\n", (total_time / generation));
}

static inline void	compute_offsets_x(t_camera *cam)
{
	cam->x_offset = vec3_add(cam->x_offset, cam->pixel_delta_u);
	cam->pixel_center = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center, cam->y_offset);
}

static inline void	compute_offsets_y(t_camera *cam)
{
	cam->y_offset = vec3_add(cam->y_offset, cam->pixel_delta_v);
	cam->pixel_center = vec3_add(cam->pixel00_loc, cam->x_offset);
	cam->pixel_center = vec3_add(cam->pixel_center, cam->y_offset);
}

void	compute(t_data *data)
{
	t_camera	*cam;
	t_scene		*scene;
	t_ray		ray;
	int			x;
	int			y;

	scene = &data->scene;
	cam = &data->scene.camera;
	cam->y_offset = cam->pixel_delta_v;
	fill_camera(cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		cam->x_offset = cam->pixel_delta_u;
		compute_offsets_y(cam);
		while (x < WIDTH)
		{
			compute_offsets_x(cam);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ft_mlx_pixel_put(&data->mlx->img, vec2i(x, y),
				ray_path(&ray, scene).rgb);
			++x;
		}
		++y;
	}
	((t_object *)(scene->lights.data))[0].light.pos.x -= 0.01;
}

void	update_fps(t_rast_env *env);
void	draw_text(t_text *text);

int	loop(t_data *data)
{
	update_fps(data->font_env);
	handle_camera_move(&data->scene.camera, data->keys);
	if (DEBUG || PERF)
		frame_gen((void (*)(void *))(&compute), (void *)data);
	else
		compute(data);
	draw_text(data->font_env->fps);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	return (0);
}
