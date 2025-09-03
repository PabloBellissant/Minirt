/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/03 23:39:22 by jaubry--         ###   ########.fr       */
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
void	handle_camera_move(t_data *data, t_camera *cam, t_keys keys);

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
	if (data->params.bvh_debug && data->scene.bvh)
		rasterize_cuboid(&data->scene.bvh->cuboid, &data->mlx->img,cam, 0xFFFF00);
	//rasterize_cuboid(&scene->bvh->next_a->cuboid, &data->mlx->img, &scene->camera, 0xFF00FF);
	//rasterize_cuboid(&scene->bvh->next_b->cuboid, &data->mlx->img, &scene->camera, 0xFF00FF);
}

void	update_fps(t_data *data);
void	draw_text(t_text *text);

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
