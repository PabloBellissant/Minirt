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

typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_texture	t_texture;
typedef struct s_data		t_data;

typedef enum e_object_type
{
	UNDEFINED,
	AMBIENT,
	CAMERA,
	LIGHT,
	MULTI_LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	OBJ_ENUM_SIZE
}	t_object_type;

int				parse_scene(char *file_name, t_scene *scene);
int				rt_parser(int fd, t_scene *scene);
int				fill_by_type(t_scene *scene);
int				parse_line(t_scene *scene, const char *line, int actual_line);
t_object_type	get_type(const char *line);
int				check_double(t_object_type type);
t_object		*create_object(t_scene *scene, t_object_type type);
t_texture		*create_texture(t_scene *scene, char *texture_path);
t_texture		*get_texture(t_scene *scene, char *texture_name);

int				ambient(const char *line, int line_num, t_scene *scene);
int				camera(const char *line, int line_num, t_scene *scene);
int				light(const char *line, int line_num, t_scene *scene);
int				sphere(const char *line, int line_num, t_scene *scene);
int				plane(const char *line, int line_num, t_scene *scene);
int				cylinder(const char *line, int line_num, t_scene *scene);
int				obj(const char *line, int line_num, t_scene *scene);
int				tex(const char *line, int line_num, t_scene *scene);
int				sky(const char *line, int line_num, t_scene *scene);

#endif
