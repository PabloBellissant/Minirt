/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:29:51 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/06 04:30:37 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

#define STEP 0.2f
#define H_COUNT 16
#define V_COUNT 24

static void	draw_horizontal_lines(t_sphere *s, t_img_data *img,
				t_camera *camera, t_rgb_int color);
static void	draw_vertical_lines(t_sphere *s, t_img_data *img,
				t_camera *camera, t_rgb_int color);

int	rasterize_sphere(t_sphere *s, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	draw_vertical_lines(s, img, camera, color);
	draw_horizontal_lines(s, img, camera, color);
	return (0);
}

static void	draw_vertical_lines(t_sphere *s, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	float	val;
	t_vec3	point;
	t_vec3	prev_point;
	int		i;

	i = 0;
	while (i < V_COUNT)
	{
		val = 0.0f;
		while (val <= 2.0f * M_PI + STEP)
		{
			point.x = s->pos.x + s->diameter / 2.1f * sinf(val)
				* cosf(i * 2.0f * M_PI / V_COUNT);
			point.y = s->pos.y + s->diameter / 2.1f * cosf(val);
			point.z = s->pos.z + s->diameter / 2.1f * sinf(val)
				* sinf(i * 2.0f * M_PI / V_COUNT);
			if (val != 0.0f)
				draw_only_visible(img, &point, &prev_point, color.rgb, camera);
			prev_point = point;
			val += STEP;
		}
		++i;
	}
}

static void	draw_horizontal_lines(t_sphere *s, t_img_data *img,
	t_camera *camera, t_rgb_int color)
{
	float	val;
	t_vec3	point;
	t_vec3	prev_point;
	int		i;

	i = 0;
	while (i < H_COUNT)
	{
		val = 0.0f;
		while (val <= 2.0f * M_PI + STEP)
		{
			point.x = s->pos.x + s->diameter / 2.01f * sinf(i * M_PI
					/ H_COUNT) * cosf(val);
			point.y = s->pos.y + s->diameter / 2.01f * cosf(i * M_PI / H_COUNT);
			point.z = s->pos.z + s->diameter / 2.01f * sinf(i * M_PI
					/ H_COUNT) * sinf(val);
			if (val != 0.0f)
				draw_only_visible(img, &prev_point, &point, color.rgb, camera);
			prev_point = point;
			val += STEP;
		}
		++i;
	}
}
