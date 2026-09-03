/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:45:02 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 17:58:15 by jaubry--         ###   ########.fr       */
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

typedef cl_float3			t_cl_rgb3;

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
}				t_camera;

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
	t_rgb			ambient;
	t_camera		camera;
	char			*name;
	t_vector		objects;
	t_vector		light;
	int				plane_count;
	t_vector		texture;
	t_vector		mat;
	t_vector		mtl_list;
	t_vector		mesh;
	t_bvh_engine	bvh;
	t_mlx			*mlx;
	int				skybox_tex;
	cl_mem			spheres;
	cl_mem			triangles;
	cl_mem			planes;
	cl_mem			textures;
	cl_mem			mats;
	cl_mem			lights;
	t_texture_data	skybox;
}					t_scene;

typedef struct s_3d_line
{
	t_vec3	pos1;
	t_vec3	pos2;
}			t_3d_line;

typedef struct s_data		t_data;
typedef struct s_params		t_params;
typedef struct s_buffers	t_buffers;

t_rgb_int	bvh_heat_color(int depth, int max_depth);
int			rasterize_cuboid_heat(t_cuboid *c, t_img_data *img,
				t_camera *camera, t_rgb_int color);
int			rasterize_sphere_heat(t_sphere *s, t_img_data *img,
				t_camera *camera, t_rgb_int color);
int			rasterize_obb_heat(t_bvh_obb *obb, t_img_data *img,
				t_camera *camera, t_rgb_int color);

int			rasterize_cuboid(t_cuboid *cuboid, t_img_data *img,
				t_camera *camera, t_rgb_int color);
int			rasterize_obb(t_bvh_obb *obb, t_img_data *img,
				t_camera *camera, t_rgb_int color);
int			rasterize_sphere_outline(t_sphere *s, t_img_data *img,
				t_camera *camera, t_rgb_int color);
t_vec2i		project_point(const t_vec3 *p, const t_camera *camera,
				const t_img_data *img);

void		get_cuboid_vertice(t_vec3 vertices[8], t_cuboid *cuboid);

void		rasterize_triangle_outline(t_img_data *img, t_triangle *triangle,
				t_rgb_int color, t_camera *camera);
void		rasterize_outline_object(t_img_data *img, t_object *object,
				t_camera *camera, t_rgb_int color);
void		draw_circle(t_img_data *img, t_vec2i pos, int radius,
				t_rgb_int color);
void		rasterize_light_outline(t_img_data *img, t_light *light,
				t_camera *camera);
void		rasterize_plane_outline(t_img_data *img, t_plane *plane,
				t_rgb_int color, t_camera *camera);
void		rasterize_3d_line(t_img_data *img, t_3d_line *line,
				t_rgb_int color, t_camera *camera);
void		rasterize_selected(t_img_data *img, t_vector objects,
				t_camera *cam);

void		export_to_ppm(t_data *data, t_mlx *mlx);
void		fill_camera(t_camera *cam, t_img_data *img);
bool		render_changed(t_data *data);
bool		cam_has_moved(t_camera *camera);

int			monte_carlo_kernel(t_opencl *cl_state, t_data *data,
				t_img_data *img);
int			normal_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);
int			pbr_kernel(t_opencl *c, t_data *data, t_img_data *img);
int			phong_kernel(t_opencl *c, t_data *data, t_img_data *img);
int			accu_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);
int			heat_kernel(t_opencl *cl_state, t_data *data, t_img_data *img);

int			phong_render(t_data *data, t_img_data *img);
int			monte_carlo_render(t_data *data, t_img_data *img);
int			pbr_render(t_data *data, t_img_data *img);
int			heat_render(t_data *data, t_img_data *img);
int			normal_render(t_data *data, t_img_data *img);
int			wireframe_render(t_data *data, t_img_data *img);

void		cast_rays_kernel(t_opencl *cl_state, t_img_data *img, t_data *data);

#endif
