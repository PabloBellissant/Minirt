/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:44:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/06 09:23:11 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "libft.h"

typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_texture	t_texture;
typedef struct s_mat		t_mat;
typedef struct s_data		t_data;

typedef enum e_object_type
{
	UNDEFINED,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	TEXTURE,
	SKYBOX,
	MATERIAL,
	OBJ_ENUM_SIZE
}	t_object_type;

typedef struct s_vertex t_vertex;

typedef struct s_obj_vectors
{
	t_vector	*tex;
	t_vector	*mat;
	t_vector	vertex;
	t_vector	normal;
	t_vector	uv;
	t_vector	triangle;
}	t_obj_vectors;

typedef struct s_pos_attribute
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	scale;
}	t_pos_attribute;

typedef union u_rgb_int t_rgb_int;

int				parse_scene(char *file_name, t_scene *scene);
int				rt_parser(int fd, t_scene *scene);
int				fill_by_type(t_scene *scene);
int				parse_line(t_scene *scene, const char *line, int actual_line);
t_object_type	get_type(const char *line);
int				check_double(t_object_type type);
t_object		*create_object(t_scene *scene, t_object_type type);
t_texture		*create_texture(t_vector *vec);
t_texture		*parse_texture(t_scene *scene, char *texture_path);
int				create_color_texture(t_vector *vec, t_rgb_int *color);
int				create_binary_texture(t_vector *vec, unsigned char value);
int				get_texture(t_scene *scene, char *texture_name);
t_mat			*create_mat(t_vector *mat);
t_mat			create_default_mat(void);
int				create_null_texture(t_vector *vec);
int				create_null_nmap(t_vector *vec);
int				create_null_roughness(t_vector *vec);
int				create_null_ambient(t_vector *vec);
int				create_null_opacity(t_vector *vec);
int				get_mat(const char *mat_name, t_scene *scene, t_rgb_int *color);

int				ambient(const char *line, int line_num, t_scene *scene);
int				camera(const char *line, int line_num, t_scene *scene);
int				light(const char *line, int line_num, t_scene *scene);
int				sphere(const char *line, int line_num, t_scene *scene);
int				plane(const char *line, int line_num, t_scene *scene);
int				cylinder(const char *line, int line_num, t_scene *scene);
int				obj(const char *line, int line_num, t_scene *scene);
int				tex(const char *line, int line_num, t_scene *scene);
int				sky(const char *line, int line_num, t_scene *scene);
int				mtl(const char *line, int line_num, t_scene *scene);

int				parse_mtl_file(int fd, t_scene *scene);
int				parse_mtl_type(const char *line, t_scene *scene);
int				newmtl(const char *line, t_scene *scene);
int				ns(const char *line, t_scene *scene);
int				ka(const char *line, t_scene *scene);
int				kd(const char *line, t_scene *scene);
int				ks(const char *line, t_scene *scene);
int				map_kd(const char *line, t_scene *scene);
int				map_bump(const char *line, t_scene *scene);
int				map_pr(const char *line, t_scene *scene);
int				map_ka(const char *line, t_scene *scene);
int				map_d(const char *line, t_scene *scene);
int				d(const char *line, t_scene *scene);
int				kr(const char *line, t_scene *scene);
int				ni(const char *line, t_scene *scene);
int				pr(const char *line, t_scene *scene);


#endif
