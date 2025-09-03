/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:45:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:18:35 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "libft.h"
# include "mlx_wrapper.h"
# include "object.h"
# include "bvh.h"

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	hit_normal;
	t_rgb	hit_rgb;
}			t_ray;

typedef struct s_phong
{
	t_vec3	*l;//direction toward light from surface
	t_vec3	*r;//direction of reflection of light from surface
	t_rgb	*d;//LIGHTS color
	t_vec3	v;//direction towards camera
}			t_phong;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	rot;
	int		fov;
	float	focal_length;
	float	theta;
	float	aspect_ratio;
	float	viewport_height;
	float	viewport_width;
	float	cos_pitch;
	float	sin_pitch;
	float	cos_yaw;
	float	sin_yaw;
	t_vec3	camera_forward;
	t_vec3	camera_right;
	t_vec3	camera_up;
	t_vec3	u;
	t_vec3	v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_vec3	focal_vec;
	t_vec3	viewport_upper_left;
	t_vec3	half_pixel_offset;
	t_vec3	pixel00_loc;
	t_vec3	pixel_center;
	t_vec3	x_offset;
	t_vec3	y_offset;
}			t_camera;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	char		*name;
	t_vector	objects;
	t_vector	lights;
	t_phong		phong;
	t_object	*planes;
	int			plane_count;
	t_bvh		*bvh;
}				t_scene;

int		rasterize_bvh(t_bvh *bvh, t_img_data *img, t_camera *camera);
t_vec2i	projection_matrix(t_vec3 *p, t_camera *camera);

#endif