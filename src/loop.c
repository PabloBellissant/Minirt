/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:22:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 03:10:20 by jaubry--         ###   ########.fr       */
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

static void	calc_bvh_bound(t_camera *cam, t_bound *bound, t_cuboid *bvh_cuboid)
{
	t_vec3	vertices[8];
	t_vec2i	proj;
	int		i;

	ft_bzero(bound, sizeof(t_bound));
	vertices[0] = bvh_cuboid->min;
	vertices[1] = vec3(bvh_cuboid->max.x, bvh_cuboid->min.y, bvh_cuboid->min.z);
	vertices[2] = vec3(bvh_cuboid->max.x, bvh_cuboid->max.y, bvh_cuboid->min.z);
	vertices[3] = vec3(bvh_cuboid->min.x, bvh_cuboid->max.y, bvh_cuboid->min.z);
	vertices[4] = vec3(bvh_cuboid->min.x, bvh_cuboid->min.y, bvh_cuboid->max.z);
	vertices[5] = vec3(bvh_cuboid->max.x, bvh_cuboid->min.y, bvh_cuboid->max.z);
	vertices[6] = vec3(bvh_cuboid->max.x, bvh_cuboid->max.y, bvh_cuboid->max.z);
	vertices[7] = vec3(bvh_cuboid->min.x, bvh_cuboid->max.y, bvh_cuboid->max.z);
	i = 0;
	bound->top = 0;
	bound->down = HEIGHT - 1;
	bound->left = 0;
	bound->right = WIDTH - 1;
	while (i < 8)
	{
		proj = project_point(&vertices[i], cam);
		if (proj.x == -1)
		{
			bound->top = 0;
			bound->down = HEIGHT - 1;
			bound->left = 0;
			bound->right = WIDTH - 1;
			return ;
		}
		if (proj.y < bound->top)
			bound->top = proj.y;
		if (proj.y > bound->down)
			bound->down = proj.y;
		if (proj.x < bound->left + 1)
			bound->left = proj.x;
		if (proj.x > bound->right)
			bound->right = proj.x + 1;
		++i;
	}
	if (bound->top < 0)
		bound->top = 0;
	if (bound->left < 0)
		bound->left = 0;
	if (bound->down < 0)
		bound->down = 0;
	if (bound->right < 0)
		bound->right = 0;
	if (bound->right > WIDTH)
		bound->right = WIDTH;
	if (bound->down > HEIGHT)
		bound->down = HEIGHT;
	if (bound->left > WIDTH)
		bound->left = WIDTH;
	if (bound->top > HEIGHT)
		bound->top = HEIGHT;
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

void	compute(t_data *data)
{
	t_camera	*cam;
	t_scene		*scene;
	t_ray		ray;
	t_vec2i		pixel;

	scene = &data->scene;
	cam = &data->scene.camera;
	fill_camera(cam);
	if (scene->plane_count == 0)
	{
		clear_old_screen(&data->mlx->img, &scene->bvh_bound);
		calc_bvh_bound(&data->scene.camera, &scene->bvh_bound, &data->scene.bvh->cuboid);
	}
	else
		scene->bvh_bound = (t_bound) {.right = WIDTH, .down = HEIGHT};
	pixel.y = scene->bvh_bound.top;
	cam->y_offset = vec3_scale(cam->pixel_delta_v, pixel.y + 1);
	while (pixel.y < scene->bvh_bound.down)
	{
		pixel.x = scene->bvh_bound.left;
		cam->x_offset =		vec3_scale(cam->pixel_delta_u, pixel.x + 1);
		compute_offsets_y(cam);
		while (pixel.x < scene->bvh_bound.right)
		{
			compute_offsets_x(cam);
			ray.pos = cam->pos;
			ray.dir = vec3_normalize(vec3_sub(cam->pixel_center, cam->pos));
			ft_mlx_pixel_put(&data->mlx->img, pixel,
				ray_path(&ray, scene).rgb);
			++pixel.x;
		}
		++pixel.y;
	}
	if (data->params.bvh_debug && data->scene.bvh)
		rasterize_bvh(scene->bvh, data->params.bvh_depth, scene->bvh->depth, data);
	// t_sphere	sphere;
	// sphere.rgb = (t_rgb) {{1, 1, 1}};
	// sphere.pos = (t_vec3) {{0, 0, 0}};
	// sphere.diameter = 25;
	// sphere.radius_squared = 126.25f;
	// rasterize_sphere(&sphere, &data->mlx->img, &scene->camera, (t_rgb_int) {.rgb = 0x00FFFF});
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
