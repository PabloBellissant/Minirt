/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:27:00 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:27:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	get_obj_type(const char *line);

int	parse_vertex(const char *line, t_vector *vertex, t_obj_attribute *attr);
int	parse_normal(const char *line, t_vector *normal_vec);
int	parse_face(const char *line, t_obj_vectors *vec, t_scene *scene, int mat_id);
int	parse_uv(const char *line, t_vector *uv_vec);
int	parse_mtllib(const char *line, t_scene *scene);
int	apply_mtl(const char *line, t_scene *scene, int *mat_id);
int	gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color);

int	parse_obj_type(const char *line, t_scene *scene, t_obj_attribute *attr, t_obj_vectors *vec)
{
	t_obj			type;
	static int		mat_id = -1;

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_obj_type(line);
	if (type == mtllib)
		return (parse_mtllib(line, scene));
	if (type == usemtl)
		return(apply_mtl(line, scene, &mat_id));
	if (type == v)
		return(parse_vertex(line, &vec->vertex, attr));
	if (type == vn)
		return(parse_normal(line, &vec->normal));
	if (type == f)
	{
		if (mat_id == -1)
			return (error(pack_err(RT_ID, RT_E_OBJ_NO_MAT), FL, LN, FC));
		return(parse_face(line, vec, scene, mat_id));
	}
	if (type == vt)
		return(parse_uv(line, &vec->uv));
	return (0);
}
