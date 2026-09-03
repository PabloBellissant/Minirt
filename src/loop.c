/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/19 14:38:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "bvh.h"
#include "render.h"
#include "minirt.h"

void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys);

bool	cam_has_moved(t_camera *camera)
{
	static t_vec3	pos;
	static t_vec3	rot;
	static int		fov;
	static float	lens_radius;
	static float	focus_dist;

	if ((ft_memcmp(&camera->pos, &pos, sizeof(t_vec3)) != 0)
		|| (ft_memcmp(&camera->rot, &rot, sizeof(t_vec3)) != 0)
		|| (fov != camera->fov) || (lens_radius != camera->lens_radius)
		|| (focus_dist != camera->focus_dist))
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
	static int		render;

	params.exposure = data->params.exposure;
	if (ft_memcmp(&data->params, &params, sizeof(t_params)) != 0
		|| (data->params.render_mode && *data->params.render_mode != render))
	{
		params = data->params;
		if (data->params.render_mode)
			render = *data->params.render_mode;
		return (true);
	}
	return (false);
}

void	export_render_task(t_data *data, t_mlx *mlx);

void	rasterize_objects(
			t_img_data *img, t_vector objects, t_camera *cam, t_rgb_int col);
void	update_fps(t_data *data);
void	fps_counter(int frame);
void	draw_select(t_vec2i mouse_pos[2], t_mlx *mlx_data);
void	debug_rasterize_bvh(t_data *data);

int	loop(t_data *data)
{
	static int	(*render_func[])(t_data *, t_img_data *img)
		= {wireframe_render, phong_render, pbr_render,
		monte_carlo_render, normal_render, heat_render};

	handle_camera_move(data, &data->scene.camera, data->keys);
	if (render_func[*data->params.render_mode](data, &data->mlx->img) != 0)
	{
		mlx_loop_end(data->mlx->mlx);
		return (1);
	}
	rasterize_selected(
		&data->mlx->img, data->ui.selection.selected, &data->scene.camera);
	export_render_task(data, data->mlx);
	update_fps(data);
	draw_select(data->ui.selection.mouse_pos, data->mlx);
	render_hierarchy(&data->ui.htree);
	debug_rasterize_bvh(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img.img, 0, 0);
	if (PERF)
		fps_counter(data->scene.camera.frame);
	return (0);
}
