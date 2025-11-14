/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:45:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/04 06:14:38 by jaubry--         ###   ########.fr       */
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
	t_vec3	hit_tangent;
	t_vec3	hit_bitangent;
	t_rgb	hit_rgb;
	float	hit_roughness;
	float	hit_ambient;
	float	hit_opacity;
	t_mat	*hit_mat;
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
	t_vec3	pixel_center_x;
	t_vec3	x_offset;
	t_vec3	y_offset;
}			t_camera;

typedef struct s_bvh_main
{
	void			*bvh_pointer;
	union
	{
		void			*bvh;
		t_aabb_bvh		*aabb_bvh;
		t_sphere_bvh	*sphere_bvh;
	};
	int			bvh_mode;
}	t_bvh_main;

typedef struct s_texture
{
	char		*pixels;
	int			tex_bpp;
	int			tex_size_line;
	int			width;
	int			height;
	char		*name;
}	t_texture;

typedef enum e_mtl
{
	no_mtl = 0,
	e_newmtl,
	e_Ns,
	e_Ka,
	e_Kd,
	e_Ks,
	e_Ke,
	e_Ni,
	e_d,
	e_illum,
	e_normal,
	e_map_kd,
	e_map_d
}	t_mtl;

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
	t_bvh_main	bvh;
	t_vector	texture;
	t_vector	mat;
	t_mlx		*mlx;
	int			skybox_tex;
}				t_scene;

typedef struct s_3d_line
{
	t_vec3	pos1;
	t_vec3	pos2;
}	t_3d_line;

typedef struct s_data t_data;
typedef struct s_params t_params;

int		rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
	t_camera *camera, t_rgb_int color);
int		rasterize_sphere_outline(t_sphere *s, t_img_data *img,
	t_camera *camera, t_rgb_int color);
void	rasterize_bvh(void *bvh, t_params *p, int total_depth, t_data *data);
t_vec2i	project_point(t_vec3 *p, t_camera *camera);
void	get_cuboid_vertice(t_vec3 vertices[8], t_cuboid *cuboid);
void	rasterize_3d_line(t_img_data *img, t_3d_line *line,
	int color, t_camera *camera);

void	rasterize_triangle_outline(t_img_data *img, t_triangle *triangle,
	int color, t_camera *camera);
void	rasterize_outline_object(t_img_data *img, t_object *object,
	t_camera *camera, t_rgb_int color);
void	draw_circle(t_img_data *img, t_vec2i pos, int radius, int color);
void	rasterize_light_outline(t_img_data *img, t_light *light,
	t_camera *camera);
void	rasterize_plane_outline(t_img_data *img, t_plane *plane,
	int color, t_camera *camera);
void	rasterize_cylinder_outline(t_img_data *img, t_cylinder *cylinder,
	int color, t_camera *camera);
void	rasterize_3d_line(t_img_data *img, t_3d_line *line,
	int color, t_camera *camera);

void	wireframe_render(t_data *data);
void	ray_tracing_render(t_data *data);

#endif
