/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 00:19:26 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "draw.h"
#include "vectors.h"
#include "calc.h"
#include "minirt.h"

void	fill_camera(t_camera *cam);
void	handle_camera_move(t_camera *cam, t_keys keys);

static void	frame_gen(void compute(t_data *), t_data *mlx)
{
	static struct timeval	start;
	static struct timeval	stop;
	static size_t			total_time = 0;
	static size_t			generation = 0;
	size_t					frame_time;

	gettimeofday(&start, NULL);
	compute(mlx);
	gettimeofday(&stop, NULL);
	frame_time = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	total_time += frame_time;
	generation++;
	printf("Frame time: %zu μs\n", frame_time);
	printf("Average: %zu μs (frame: %zu)\n", total_time / generation,
		generation);
}

static void	compute_offsets(t_camera *cam, int x, int y)
{
	cam->pixel_center = cam->pixel00_loc;
	cam->x_offset = vec3_scale(cam->pixel_delta_u, (float)x);
	cam->y_offset = vec3_scale(cam->pixel_delta_v, (float)y);
	cam->pixel_center = vec3_add(cam->pixel_center, cam->x_offset);
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
	fill_camera(cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			compute_offsets(cam, x, y);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			put_pixel(data->addr, x, y, ray_path(&ray, scene).rgb);
			++x;
		}
		++y;
	}
	((t_object *)(scene->lights.data))[0].light.pos.x -= 1;
}

void	update_fps(t_rast_env *env);
void	draw_text(t_text *text);

int	loop(t_data *data)
{
	update_fps(data->font_env);
	handle_camera_move(&data->scene.camera, data->keys);
	if (DEBUG || PERF)
		frame_gen(&compute, data);
	else
		compute(data);
	draw_text(data->font_env->fps);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
