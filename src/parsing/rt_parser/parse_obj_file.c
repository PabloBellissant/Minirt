/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 02:28:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/02 02:29:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "minirt.h"

#define VERTEX_FORMAT " *v  *%f *%f *%f *"
#define TEXTURE_FORMAT " *vt  *%f *%f *"
#define NORMAL_FORMAT " *vn  *%f *%f *%f *"
#define FACE_FORMAT " *f  *%d */ *%d */ *%d  *%d */ *%d */ *%d  *%d */ *%d */ *%d  *\n"

typedef enum e_obj
{
	null = 0,
	vn,
	vt,
	v,
	f
}	t_obj;

t_obj	get_obj_type(const char *line);
int		parse_vertex(const char *line, int line_num, t_vector *vertex, t_vec3 *pos);
int		parse_normal(const char *line, int line_num, t_vector *normal_vec);
int		parse_face(const char *line, int line_num, t_vector *vertex, t_vector *normal, t_vector *uv, t_scene *scene);
int		parse_texture(const char *line, int line_num, t_vector *uv_vec);

int	parse_obj_file(int fd, t_scene *scene, t_vec3 *pos)
{
	char		*line;
	t_vector	vertex_vec;
	t_vector	normal_vec;
	t_vector	triangle_vec;
	t_vector	uv_vec;
	int			line_num;
	t_obj		type;
	int			triangle_count;
	int			ret_val;

	if (fd == -1)
		return (-1);
	triangle_count = 0;
	vector_init(&vertex_vec, sizeof(t_vertex));
	vector_init(&normal_vec, sizeof(t_vec3));
	vector_init(&uv_vec, sizeof(t_vec2));
	vector_init(&triangle_vec, sizeof(t_triangle));
	line = get_next_line(fd);
	line_num = 0;
	ret_val = 0;
	while (line != NULL)
	{
		type = get_obj_type(line);
		if (type == v)
			ret_val = parse_vertex(line, line_num, &vertex_vec, pos);
		else if (type == vn)
			ret_val = parse_normal(line, line_num, &normal_vec);
		else if (type == f)
		{
			++triangle_count;
			ret_val = parse_face(line, line_num, &vertex_vec, &normal_vec,
				&uv_vec, scene);
		}
		else if (type == vt)
			ret_val = parse_texture(line, line_num, &uv_vec);
		++line_num;
		line = get_next_line(fd);
		if (ret_val == -1)
		{
			free(vertex_vec.data);
			free(normal_vec.data);
			free(uv_vec.data);
			free(triangle_vec.data);
			return (-1);
		}
	}
	free(vertex_vec.data);
	free(normal_vec.data);
	free(uv_vec.data);
	ft_printf("Triangle count : %d\n", triangle_count);
	return (0);
}

t_obj	get_obj_type(const char *line)
{
	static const char	*elem[] = {"vn", "vt", "v", "f", NULL};
	int			i;

	while (*line == ' ' || *line == '\t')
		++line;
	i = 0;
	while (elem[i])
	{
		if (ft_strncmp(elem[i], line, ft_strlen(elem[i])) == 0)
		{
			if ((*(line + ft_strlen(elem[i])) == ' ')
				|| (*(line + ft_strlen(elem[i])) == '\t'))
				return ((t_obj) i + 1);
		}
		++i;
	}
	return (null);
}

int	parse_texture(const char *line, int line_num, t_vector *uv_vec)
{
	t_vec2	uv;

	if (ft_scan(line_num, TEXTURE_FORMAT, line, &uv.x, &uv.y))
		return (-1);
	if (vector_add(uv_vec, &uv, 1) == -1)
		return (-1);
	return (0);
}

int	parse_vertex(const char *line, int line_num, t_vector *vertex, t_vec3 *pos)
{
	t_vertex	v;

	if (ft_scan(line_num, VERTEX_FORMAT, line, &v.pos.x, &v.pos.y, &v.pos.z))
		return (-1);
	v.pos = vec3_add(v.pos, *pos);
	if (vector_add(vertex, &v, 1) == -1)
		return (-1);
	return (0);
}

int	parse_normal(const char *line, int line_num, t_vector *normal_vec)
{
	t_vec3	normal;

	if (ft_scan(line_num, NORMAL_FORMAT, line, &normal.x, &normal.y, &normal.z))
		return (-1);
	if (vector_add(normal_vec, &normal, 1) == -1)
		return (-1);
	return (0);
}

int	parse_face(const char *line, int line_num, t_vector *vertex, t_vector *normal, t_vector *uv, t_scene *scene)
{
	int			vertex_id[3];
	int			uv_id[3];
	int			normal_id[3];
	t_object	*o;

	o = create_object(scene, TRIANGLE);
	if (o == NULL)
		return (-1);
	if (ft_scan(line_num, FACE_FORMAT, line,
		&vertex_id[0], &uv_id[0], &normal_id[0],
		&vertex_id[1], &uv_id[1], &normal_id[1],
		&vertex_id[2], &uv_id[2], &normal_id[2]))
		return (-1);
	o->triangle.p0 = *(t_vertex *)get_vector_value(vertex, (size_t)vertex_id[0] - 1);
	o->triangle.p1 = *(t_vertex *)get_vector_value(vertex, (size_t)vertex_id[1] - 1);
	o->triangle.p2 = *(t_vertex *)get_vector_value(vertex, (size_t)vertex_id[2] - 1);
	o->triangle.p0.norm = *(t_vec3 *)get_vector_value(normal, (size_t)normal_id[0] - 1);
	o->triangle.p1.norm = *(t_vec3 *)get_vector_value(normal, (size_t)normal_id[1] - 1);
	o->triangle.p2.norm = *(t_vec3 *)get_vector_value(normal, (size_t)normal_id[2] - 1);
	(void) uv;
	// o->triangle.p0.uv = *(t_vec2 *)get_vector_value(uv, uv_id[0] - 1);
	// o->triangle.p1.uv = *(t_vec2 *)get_vector_value(uv, uv_id[1] - 1);
	// o->triangle.p2.uv = *(t_vec2 *)get_vector_value(uv, uv_id[2] - 1);
	o->triangle.rgb = vec3(1,0,1);
	o->triangle.edge_1 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
	o->triangle.edge_2 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
	o->f = hit_triangle;
	return (0);
}
