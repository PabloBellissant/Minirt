/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_face.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:23:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:23:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "calc.h"
#include "parsing.h"

#define FACE_FORMAT " *f  *%d */ *%d */ *%d  *%d */ *%d */ *%d  *%d */ *%d */ *%d  *\n"

static void	*get_value(t_vector *vec, int value);
static void apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3]);
static void apply_normal(t_triangle *triangle, t_vector *vec, int normal[3]);
static void apply_uv(t_triangle *triangle, t_vector *vec, int uv[3]);

int	parse_face(const char *line, t_obj_vectors *vec, t_scene *scene, int mat_id)
{
	int			vertex_id[3];
	int			uv_id[3];
	int			normal_id[3];
	t_object	*obj;

	obj = create_object(scene, TRIANGLE);
	if (obj == NULL)
		return (-1);
	if (ft_scan(0, FACE_FORMAT, line,
		&vertex_id[0], &uv_id[0], &normal_id[0],
		&vertex_id[1], &uv_id[1], &normal_id[1],
		&vertex_id[2], &uv_id[2], &normal_id[2]))
		return (-1);
	apply_vertex(&obj->triangle, &vec->vertex, vertex_id);
	apply_normal(&obj->triangle, &vec->normal, normal_id);
	apply_uv(&obj->triangle, &vec->uv, uv_id);
	obj->triangle.edge_1 = vec3_sub(obj->triangle.p1.pos, obj->triangle.p0.pos);
	obj->triangle.edge_2 = vec3_sub(obj->triangle.p2.pos, obj->triangle.p0.pos);
	obj->mat_id = mat_id;
	obj->f = hit_triangle;
	return (0);
}

static void	*get_value(t_vector *vec, int value)
{
	if (value > (int)vec->num_elements)
		return (NULL);
	return (get_vector_value(vec, (size_t)value - 1));
}

static void apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3])
{
	triangle->p0 = *(t_vertex *)get_value(vec, vertex[0]);
	triangle->p1 = *(t_vertex *)get_value(vec, vertex[1]);
	triangle->p2 = *(t_vertex *)get_value(vec, vertex[2]);
}

static void apply_normal(t_triangle *triangle, t_vector *vec, int normal[3])
{
	triangle->p0.norm = *(t_vec3 *)get_value(vec, normal[0]);
	triangle->p1.norm = *(t_vec3 *)get_value(vec, normal[1]);
	triangle->p2.norm = *(t_vec3 *)get_value(vec, normal[2]);
}

static void apply_uv(t_triangle *triangle, t_vector *vec, int uv[3])
{
	triangle->p0.uv = *(t_vec2 *)get_value(vec, uv[0]);
	triangle->p1.uv = *(t_vec2 *)get_value(vec, uv[1]);
	triangle->p2.uv = *(t_vec2 *)get_value(vec, uv[2]);
}
