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

static int apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3]);
static int apply_normal(t_triangle *triangle, t_vector *vec, int normal[3]);
static int apply_uv(t_triangle *triangle, t_vector *vec, int uv[3]);

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
	{
		return (-1);
	}
	if (apply_vertex(&obj->triangle, &vec->vertex, vertex_id) == -1
		|| apply_normal(&obj->triangle, &vec->normal, normal_id) == -1
		|| apply_uv(&obj->triangle, &vec->uv, uv_id) == -1)
	{
		return (-1);
	}
	obj->triangle.edge_1 = vec3_sub(obj->triangle.p1.pos, obj->triangle.p0.pos);
	obj->triangle.edge_2 = vec3_sub(obj->triangle.p2.pos, obj->triangle.p0.pos);
	obj->mat_id = mat_id;
	obj->f = hit_triangle;
	return (0);
}

static int apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3])
{
	if (vertex[0] > (int)vec->num_elements
		|| vertex[1] > (int)vec->num_elements
		|| vertex[2] > (int)vec->num_elements)
	{
		return (-1);
	}
	triangle->p0 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[0] - 1);
	triangle->p1 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[1] - 1);
	triangle->p2 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[2] - 1);
	return (0);
}

t_vec3	vec3_floor(t_vec3 vec)
{
	vec.x -= floorf(vec.x);
	vec.y -= floorf(vec.y);
	vec.z -= floorf(vec.z);
	return (vec);
}
t_vec3	rotate_point(t_vec3 pos, t_vec3 rot);
static int apply_normal(t_triangle *triangle, t_vector *vec, int normal[3])
{
	if (normal[0] > (int)vec->num_elements
		|| normal[1] > (int)vec->num_elements
		|| normal[2] > (int)vec->num_elements)
	{
		return (-1);
	}
	t_vec3	rot = triangle->p0.norm;
	triangle->p0.norm = *(t_vec3 *)get_vector_value(vec, (size_t)normal[0] - 1);
	triangle->p0.norm = rotate_point(triangle->p0.norm, rot);

	rot = triangle->p1.norm;
	triangle->p1.norm = *(t_vec3 *)get_vector_value(vec, (size_t)normal[1] - 1);
	triangle->p1.norm = rotate_point(triangle->p1.norm, rot);

	rot = triangle->p2.norm;
	triangle->p2.norm = *(t_vec3 *)get_vector_value(vec, (size_t)normal[2] - 1);
	triangle->p2.norm = rotate_point(triangle->p2.norm, rot);
	return (0);
}

static int apply_uv(t_triangle *triangle, t_vector *vec, int uv[3])
{
	if (uv[0] > (int)vec->num_elements
		|| uv[1] > (int)vec->num_elements
		|| uv[2] > (int)vec->num_elements)
	{
		return (-1);
	}
	triangle->p0.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[0] - 1);
	triangle->p1.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[1] - 1);
	triangle->p2.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[2] - 1);
	return (0);
}
