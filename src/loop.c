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

static int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	get_sphere_vertice(t_vec3 vertices[1008], t_sphere_bvh *bvh)
{
	float	val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		val = 0.0f;
		while (val <= 2.0f * M_PI)
		{
			vertices[j].x = bvh->pos.x + (bvh->size * 1.02) * sinf(i * M_PI
					/ 16) * cosf(val);
			vertices[j].y = bvh->pos.y + (bvh->size * 1.02) * cosf(i * M_PI / 16);
			vertices[j].z = bvh->pos.z + (bvh->size * 1.02) * sinf(i * M_PI
					/ 16) * sinf(val);
			++j;
			val += 0.1;
		}
		++i;
	}
}

static int	apply_bound(t_vec2i *proj, t_bound *bound)
{
	if (proj->x == -1)
	{
		bound->top = 0;
		bound->down = HEIGHT - 1;
		bound->left = 0;
		bound->right = WIDTH - 1;
		return (-1);
	}
	if (proj->y < bound->top)
		bound->top = imax(proj->y, 0);
	if (proj->y > bound->down)
		bound->down = imin(proj->y, HEIGHT - 1);
	if (proj->x < bound->left)
		bound->left = imax(proj->x, 0);
	if (proj->x > bound->right)
		bound->right = imin(proj->x, WIDTH - 1);
	return (0);
}

static void calc_sphere_bound(t_camera *cam, t_bound *bound, t_sphere_bvh *bvh)
{
	t_vec3	vertices[1008];
	t_vec2i	proj;
	int		i;

	get_sphere_vertice(vertices, bvh);
	i = 0;
	while (i < 1008)
	{
		proj = project_point(&vertices[i], cam);
		if (apply_bound(&proj, bound) == -1)
			return ;
		++i;
	}
}

static void calc_aabb_bound(t_camera *cam, t_bound *bound, t_aabb_bvh *bvh)
{
	t_vec3	vertices[8];
	t_vec2i	proj;
	int		i;

	get_cuboid_vertice(vertices, &bvh->cuboid);
	i = 0;
	while (i < 8)
	{
		proj = project_point(&vertices[i], cam);
		if (apply_bound(&proj, bound) == -1)
			return ;
		++i;
	}
}

static void	calc_bvh_bound(t_camera *cam, t_bound *bound, t_bvh_main *bvh, int mode)
{
	bvh->bound.top = HEIGHT;
	bvh->bound.down = 0;
	bvh->bound.left = WIDTH;
	bvh->bound.right = 0;
	if (mode == 0)
		calc_sphere_bound(cam, bound, bvh->sphere_bvh);
	if (mode == 1)
		calc_aabb_bound(cam, bound, bvh->aabb_bvh);
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

static void	draw_bound(t_bound *bound, t_img_data *img)
{
	t_vec2i	c1;
	t_vec2i	c2;
	t_vec2i	c3;
	t_vec2i	c4;

	c1 = vec2i(bound->left, bound->top);
	c2 = vec2i(bound->right, bound->top);
	c3 = vec2i(bound->left, bound->down);
	c4 = vec2i(bound->right, bound->down);
	ft_mlx_line_put(img, c1, c2, 0xFFFFFF);
	ft_mlx_line_put(img, c1, c3, 0xFFFFFF);
	ft_mlx_line_put(img, c2, c4, 0xFFFFFF);
	ft_mlx_line_put(img, c3, c4, 0xFFFFFF);
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
		clear_old_screen(&data->mlx->img, &scene->bvh.bound);
		calc_bvh_bound(&data->scene.camera, &scene->bvh.bound, &data->scene.bvh, scene->bvh.bvh_mode);
	}
	else
		scene->bvh.bound = (t_bound) {.right = WIDTH, .down = HEIGHT};
	pixel.y = scene->bvh.bound.top;
	cam->y_offset = vec3_scale(cam->pixel_delta_v, pixel.y + 1);
	while (pixel.y < scene->bvh.bound.down)
	{
		pixel.x = scene->bvh.bound.left;
		cam->x_offset =	vec3_scale(cam->pixel_delta_u, pixel.x + 1);
		compute_offsets_y(cam);
		while (pixel.x < scene->bvh.bound.right)
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
	if (data->params.bvh_debug && data->scene.bvh.bvh)
		rasterize_bvh(scene->bvh.bvh, &data->params, scene->bvh.sphere_bvh->depth, data);
	if (data->params.bound_debug)
		draw_bound(&scene->bvh.bound, &data->mlx->img);
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
