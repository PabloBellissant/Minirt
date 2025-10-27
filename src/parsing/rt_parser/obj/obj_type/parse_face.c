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

int	parse_face(const char *line, t_obj_vectors *vec, t_scene *scene, t_mat *m)
{
	int			vertex_id[3];
	int			uv_id[3];
	int			normal_id[3];
	t_object	*o;

	o = create_object(scene, TRIANGLE);
	if (o == NULL)
		return (-1);
	if (ft_scan(0, FACE_FORMAT, line,
		&vertex_id[0], &uv_id[0], &normal_id[0],
		&vertex_id[1], &uv_id[1], &normal_id[1],
		&vertex_id[2], &uv_id[2], &normal_id[2]))
		return (-1);
	o->triangle.p0 = *(t_vertex *)get_vector_value(&vec->vertex, (size_t)vertex_id[0] - 1);
	o->triangle.p1 = *(t_vertex *)get_vector_value(&vec->vertex, (size_t)vertex_id[1] - 1);
	o->triangle.p2 = *(t_vertex *)get_vector_value(&vec->vertex, (size_t)vertex_id[2] - 1);
	o->triangle.p0.norm = *(t_vec3 *)get_vector_value(&vec->normal, (size_t)normal_id[0] - 1);
	o->triangle.p1.norm = *(t_vec3 *)get_vector_value(&vec->normal, (size_t)normal_id[1] - 1);
	o->triangle.p2.norm = *(t_vec3 *)get_vector_value(&vec->normal, (size_t)normal_id[2] - 1);
	o->triangle.p0.uv = *(t_vec2 *)get_vector_value(&vec->uv, uv_id[0] - 1);
	o->triangle.p1.uv = *(t_vec2 *)get_vector_value(&vec->uv, uv_id[1] - 1);
	o->triangle.p2.uv = *(t_vec2 *)get_vector_value(&vec->uv, uv_id[2] - 1);
	o->triangle.edge_1 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
	o->triangle.edge_2 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
	if (m)
		o->mat = *m;
	else
		o->mat = create_default_mat();
	o->f = hit_triangle;
	return (0);
}
