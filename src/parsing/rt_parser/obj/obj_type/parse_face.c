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

#include "render.h"
#include "parsing.h"
#include "rt_xcerrcal.h"

#define FACE_FORMAT " *f  *%d */ *%d */ *%d  *%d */ *%d */ *%d  *%d */ *%d */\
*%d  *\n"

static int	apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3]);
static int	apply_normal(t_triangle *triangle, t_vector *vec, int normal[3]);
static int	apply_uv(t_triangle *triangle, t_vector *vec, int uv[3]);

int	parse_face(const char *line, t_obj_vectors *vec, t_scene *scene, int mat_id)
{
	int			ids[9];
	t_object	*o;

	o = create_object(scene, TRIANGLE);
	if (o == NULL)
		return (-1);
	if (ft_scan(0, FACE_FORMAT, line,
			&ids[0], &ids[3], &ids[6],
			&ids[1], &ids[4], &ids[7],
			&ids[2], &ids[5], &ids[8]))
		return (-1);
	if (apply_vertex(&o->triangle, &vec->vertex, ids) == -1
		|| apply_normal(&o->triangle, &vec->normal, &ids[6]) == -1
		|| apply_uv(&o->triangle, &vec->uv, &ids[3]) == -1)
		return (error(pack_err(RT_ID, LFT_E_WRN_NEWLINE), FL, LN, FC));
	o->triangle.edge_p1p0 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
	o->triangle.edge_p2p0 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
	o->triangle.d00 = vec3_dot(o->triangle.edge_p1p0, o->triangle.edge_p1p0);
	o->triangle.d01 = vec3_dot(o->triangle.edge_p1p0, o->triangle.edge_p2p0);
	o->triangle.d11 = vec3_dot(o->triangle.edge_p2p0, o->triangle.edge_p2p0);
	o->triangle.denom
		= o->triangle.d00 * o->triangle.d11 - o->triangle.d01 * o->triangle.d01;
	o->mat_id = mat_id;
	return (0);
}

static int	apply_vertex(t_triangle *triangle, t_vector *vec, int vertex[3])
{
	if (vertex[0] > (int)vec->num_elements
		|| vertex[1] > (int)vec->num_elements
		|| vertex[2] > (int)vec->num_elements)
	{
		return (error(pack_err(RT_ID, RT_E_VERTEX), FL, LN, FC));
	}
	triangle->p0 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[0] - 1);
	triangle->p1 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[1] - 1);
	triangle->p2 = *(t_vertex *)get_vector_value(vec, (size_t)vertex[2] - 1);
	return (0);
}

t_vec3		rotate_point(t_vec3 pos, t_vec3 rot);

static int	apply_normal(t_triangle *triangle, t_vector *vec, int normal[3])
{
	t_vec3	rot;

	if (normal[0] > (int)vec->num_elements
		|| normal[1] > (int)vec->num_elements
		|| normal[2] > (int)vec->num_elements)
	{
		return (error(pack_err(RT_ID, RT_E_NORMAL), FL, LN, FC));
	}
	rot = triangle->p0.norm;
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

static int	apply_uv(t_triangle *triangle, t_vector *vec, int uv[3])
{
	if (uv[0] > (int)vec->num_elements
		|| uv[1] > (int)vec->num_elements
		|| uv[2] > (int)vec->num_elements)
	{
		return (error(pack_err(RT_ID, RT_E_UV), FL, LN, FC));
	}
	triangle->p0.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[0] - 1);
	triangle->p1.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[1] - 1);
	triangle->p2.uv = *(t_vec2 *)get_vector_value(vec, (size_t)uv[2] - 1);
	return (0);
}
