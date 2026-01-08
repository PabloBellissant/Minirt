/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:45:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/12/16 00:51:04 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "colors_types.h"
# include "libft.h"
# include "mlx_wrapper.h"
# include "object.h"
# include "bvh.h"
# include "vectors_types.h"

# define MAX_ITER  5

typedef struct s_refract_pos
{
	int		count;
	t_vec3	origin[MAX_ITER];
	t_vec3	dir[MAX_ITER];
	t_rgb	through_power[MAX_ITER];
}	t_refract_pos;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			dir;
	t_vec3			inv_dir;
	t_rgb			accumulated_color;
	t_rgb			through_power;
	int				iteration;
	t_refract_pos	refract;
	bool			active;
}			t_ray;

typedef struct s_hit
{
	bool		hit;
	int			id;
	t_vec3		normal;
	t_vec2		uv;
	int			mat_id;
	t_vec3		hit_point;
	t_rgb		hit_rgb;
	float		hit_ambient;
	t_vec3		ks;
	t_vec3		ke;
	float		ns;
	t_vec3		reflectivity;
	t_object	*hit_obj;
}			t_hit;

typedef struct s_hit_mat_data
{
	t_mat	*mat;
	float	hit_opacity;
	float	roughness;
	float	metalness;
}			t_hit_mat_data;

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
	float	cos_roll;
	float	sin_roll;
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
	void		*bvh_pointer;
	union
	{
		void			*bvh;
		t_aabb_bvh		*aabb_bvh;
		t_sphere_bvh	*sphere_bvh;
	};
	int			bvh_mode;
}	t_bvh_main;

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
}	t_mtl; // to fix;

typedef struct s_scene
{
	t_rgb		ambient;
	t_camera	camera;
	char		*name;
	t_vector	objects;
	t_vector	lights;
	int			*planes_id;
	int			plane_count;
	t_bvh_main	bvh;
	t_vector	texture;
	t_vector	mat;
	t_vector	mtl_list;
	t_vector	obj_list;
	t_mlx		*mlx;
	int			skybox_tex;
	int			*emissive_id;
	int			emissive_count;
}				t_scene;

typedef struct s_3d_line
{
	t_vec3	pos1;
	t_vec3	pos2;
}	t_3d_line;

typedef struct s_data		t_data;
typedef struct s_params		t_params;
typedef struct s_buffers	t_buffers;

int		rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
			t_camera *camera, t_rgb_int color);
int		rasterize_sphere_outline(t_sphere *s, t_img_data *img,
			t_camera *camera, t_rgb_int color);
void	rasterize_bvh(void *bvh, t_params *p, int total_depth, t_data *data);
t_vec2i	project_point(t_vec3 *p, t_camera *camera, t_img_data *img);
void	get_cuboid_vertice(t_vec3 vertices[8], t_cuboid *cuboid);

void	rasterize_triangle_outline(t_img_data *img, t_triangle *triangle,
			t_rgb_int color, t_camera *camera);
void	rasterize_outline_object(t_img_data *img, t_object *object,
			t_camera *camera, t_rgb_int color);
void	draw_circle(t_img_data *img, t_vec2i pos, int radius, t_rgb_int color);
void	rasterize_light_outline(t_img_data *img, t_light *light,
			t_camera *camera);
void	rasterize_plane_outline(t_img_data *img, t_plane *plane,
			t_rgb_int color, t_camera *camera);
void	rasterize_cylinder_outline(t_img_data *img, t_cylinder *cylinder,
			t_rgb_int color, t_camera *camera);
void	rasterize_3d_line(t_img_data *img, t_3d_line *line,
			t_rgb_int color, t_camera *camera);

void	wireframe_render(t_data *data, t_img_data *img);
void	pbr_render(t_data *data, t_img_data *img);

int		export_to_ppm(t_data *data, t_mlx *mlx);

float	sample_gray_level_texture(const t_texture *texture_list,
			int id, t_vec2 uv);
t_rgb	sample_texture(const t_texture *texture_list, int id, t_vec2 uv);

void	fill_camera(t_camera *cam, t_img_data *img);
void	cast_ray_loop(
			t_camera *cam, t_buffers bu, int pixel_size, t_img_data *img);
void	intersect_loop(t_ray *rays, t_hit *hits, t_scene *scene, int count);
void	draw_skybox_loop(
			t_buffers bu, int texture_id, t_texture *texture, int size);

int		compact_hits_inplace(t_hit *buffer, int input_size);

void	path_sample_materials_loop(
			t_buffers *bu, t_texture *tex, t_mat *mat, int count);

void	path_shade_loop(t_buffers *buffers, t_scene *scene, int count);

void	normal_debug_loop(t_buffers *buffers, int count);
void	accu_screen_loop(t_buffers bu, int sample_count, t_img_data *img);

#endif
