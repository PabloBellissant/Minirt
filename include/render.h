/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:45:02 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 16:26:36 by jaubry--         ###   ########.fr       */
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
# include <CL/cl.h>

typedef cl_float3 cl_rgb3;

# define MAX_ITER  1

typedef struct s_refract_pos
{
	cl_int		count;
	cl_float3	origin[MAX_ITER];
	cl_float3	dir[MAX_ITER];
	cl_rgb3		through_power[MAX_ITER];
}	t_refract_pos;

typedef struct s_ray
{
	cl_float3		origin;
	cl_float3		dir;
	cl_float3		inv_dir;
	cl_rgb3			accumulated_color;
	cl_rgb3			through_power;
	cl_int			iteration;
	t_refract_pos	refract;
	cl_int			active;
}			t_ray;

typedef struct s_hit
{
	cl_int		hit;
	cl_int		id;
	cl_float3	normal;
	cl_float2	uv;
	cl_int		mat_id;
	cl_float3	hit_point;
	cl_rgb3		hit_rgb;
	cl_float	hit_ambient;
	cl_float3	ks;
	cl_float3	ke;
	cl_float	ns;
	cl_float3	reflectivity;
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
	cl_float3	pos;
	cl_float3	rot;
	cl_float3	camera_forward;
	cl_float3	camera_right;
	cl_float3	camera_up;
	cl_float3	pixel_delta_u;
	cl_float3	pixel_delta_v;
	cl_float3	pixel00_loc;
	cl_int		fov;
	cl_int		frame;
	cl_float	lens_radius;
	cl_float	focus_dist;
}			t_camera;

typedef struct s_bvh_main
{
	t_aabb_bvh	*triangle_bvh;
	t_aabb_bvh	*sphere_bvh;
	union
	{
		void			*bvh;
		t_sphere_bvh	*sphere_mode_bvh;
	};
	int			bvh_mode;
	int			sphere_bvh_size;
	int			triangle_bvh_size;

	t_aabb_bvh	*triangle_bvh4;
	int			triangle_bvh4_size;
	t_aabb_bvh	*sphere_bvh4;
	int			sphere_bvh4_size;

	t_aabb_bvh	*triangle_bvh8;
	int			triangle_bvh8_size;
	t_aabb_bvh	*sphere_bvh8;
	int			sphere_bvh8_size;

	cl_mem		sphere_gpu_bvh;
	cl_mem		triangle_gpu_bvh;
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
	t_vector	light;
	int			*planes_id;
	int			plane_count;
	t_bvh_main	bvh;
	t_aabb_bvh	*bvh_triangle_sah;
	int			bvh_triangle_sah_size;
	t_aabb_bvh	*bvh_sphere_sah;
	int			bvh_sphere_sah_size;
	t_vector	texture;
	t_vector	mat;
	t_vector	mtl_list;
	t_vector	obj_list;
	t_mlx		*mlx;
	int			skybox_tex;
	cl_mem		spheres;
	cl_mem		triangles;
	cl_mem		planes;
	cl_mem		textures;
	cl_mem		mats;
	cl_mem		lights;
	t_texture_data	skybox;
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
void	rasterize_bvh(void *bvh, t_params *p, int size, t_data *data);
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
void	rasterize_3d_line(t_img_data *img, t_3d_line *line,
			t_rgb_int color, t_camera *camera);

void	export_to_ppm(t_data *data, t_mlx *mlx);
void	fill_camera(t_camera *cam, t_img_data *img);
bool	render_changed(t_data *data);
bool	cam_has_moved(t_camera *camera);


int		monte_carlo_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);
int		normal_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);
int		pbr_kernel(t_opencl *c, t_data *data, t_img_data *img);
int		phong_kernel(t_opencl *c, t_data *data, t_img_data *img);
int		accu_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);
int		heat_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);

void	phong_render(t_data *data, t_img_data *img);
void	monte_carlo_render(t_data *data, t_img_data *img);
void	pbr_render(t_data *data, t_img_data *img);
void	heat_render(t_data *data, t_img_data *img);
void	normal_render(t_data *data, t_img_data *img);
void	wireframe_render(t_data *data, t_img_data *img);

#endif
