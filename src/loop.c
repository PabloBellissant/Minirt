/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 04:59:54 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "draw.h"
#include "vec3.h"
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
	cam->x_offset = cam->pixel_delta_u;
	cam->y_offset = cam->pixel_delta_v;
	vec3_scale(&cam->x_offset, (float)x);
	vec3_scale(&cam->y_offset, (float)y);
	vec3_add(&cam->pixel_center, &cam->x_offset, &cam->pixel_center);
	vec3_add(&cam->pixel_center, &cam->y_offset, &cam->pixel_center);
}

void	compute(t_data *mlx)
{
	t_camera	*cam;
	t_scene		*scene;
	t_ray		ray;
	int			x;
	int			y;

	scene = &mlx->scene;
	cam = &mlx->scene.camera;
	fill_camera(cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			compute_offsets(cam, x, y);
			ray.pos = cam->pos;
			vec3_sub(&cam->pixel_center, &cam->pos, &ray.dir);
			vec3_unit(&ray.dir);
			put_pixel(mlx->addr, x, y, ray_path(&ray, scene).rgb);
			++x;
		}
		++y;
	}
	((t_object *)(scene->lights.data))[0].light.pos.x -= 0.1;
}

int	loop(t_data *mlx)
{
	handle_camera_move(&mlx->scene.camera, mlx->keys);
	if (DEBUG || PERF)
		frame_gen(&compute, mlx);
	else
		compute(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
