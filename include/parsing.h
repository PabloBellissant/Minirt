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

typedef struct s_scene	t_scene;
typedef struct s_object	t_object;

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
	OBJ_ENUM_SIZE
}	t_object_type;

int				parse_scene(char *file_name, t_scene *scene);
int				rt_parser(int fd, t_scene *scene);
int				fill_by_type(t_scene *scene);
int				parse_line(t_scene *scene, char *line, int actual_line);
t_object_type	get_type(char *line, int actual_line);
int				check_float(t_object_type type, int actual_line);
t_object		*create_object(t_scene *scene, t_object_type type);

int				ambient(char *line, int line_num, t_scene *scene);
int				camera(char *line, int line_num, t_scene *scene);
int				light(char *line, int line_num, t_scene *scene);
int				sphere(char *line, int line_num, t_scene *scene);
int				plane(char *line, int line_num, t_scene *scene);
int				cylinder(char *line, int line_num, t_scene *scene);

#endif
