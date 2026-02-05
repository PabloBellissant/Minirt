/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 17:49:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "bvh.h"
#include "render.h"
#include "minirt.h"

void	fill_camera(t_camera *cam, t_img_data *img);
void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys);

bool	cam_has_moved(t_camera *camera)
{
	static t_vec3	pos;
	static t_vec3	rot;
	static int		fov;
	static float	lens_radius;
	static float	focus_dist;

	if (ft_memcmp(&camera->pos, &pos, sizeof(t_vec3)) != 0
		|| ft_memcmp(&camera->rot, &rot, sizeof(t_vec3)) != 0
		|| fov != camera->fov || lens_radius != camera->lens_radius
		|| focus_dist != camera->focus_dist)
	{
		pos = camera->pos;
		rot = camera->rot;
		fov = camera->fov;
		lens_radius = camera->lens_radius;
		focus_dist = camera->focus_dist;
		return (true);
	}
	return (false);
}

bool	render_changed(t_data *data)
{
	static t_params	params;

	if (ft_memcmp(&data->params, &params, sizeof(t_params)) != 0)
	{
		params = data->params;
		return (true);
	}
	return (false);
}

void	fps_counter(int frame)
{
	static int				frames = 0;
	static long				last_time = 0;
	struct timeval			tv;
	long					current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (last_time == 0)
		last_time = current_time;
	frames++;
	if (current_time - last_time >= 1000)
	{
		printf("FPS: %d, samples : %d\n", frames, frame);
		frames = 0;
		last_time = current_time;
	}
}

int	loop(t_data *data)
{
	static void	(*render_func[])(t_data *, t_img_data *img)
		= {wireframe_render, phong_render, pbr_render,
		monte_carlo_render, normal_render, heat_render};

	if (data->params.render_mode != 0)
	{
		if (!data->scene.bvh.sphere_bvh || !data->scene.bvh.triangle_bvh)
		{
			data->scene.bvh.bvh_mode = 1;
			if (load_bvh(data->scene.bvh.bvh_mode, &data->scene, &data->cl) == -1)
				return (-1);
			data->params.bvh_depth = max(data->scene.bvh.triangle_bvh->depth, data->scene.bvh.sphere_bvh->depth);
		}
	}
	handle_camera_move(data, &data->scene.camera, data->keys);
	render_func[data->params.render_mode](data, &data->mlx->img);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	if (data->params.bvh_debug && data->scene.bvh.triangle_bvh)
	{
		rasterize_bvh(data->scene.bvh.triangle_bvh4, &data->params, data->scene.bvh.triangle_bvh4->depth, data);
		rasterize_bvh(data->scene.bvh.sphere_bvh4, &data->params, data->scene.bvh.sphere_bvh4->depth, data);
	}
	fps_counter(data->scene.camera.frame);
	return (0);
}
