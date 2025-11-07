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

int	parse_vertex(const char *line, t_vector *vertex, t_vec3 *pos);
int	parse_normal(const char *line, t_vector *normal_vec);
int	parse_face(const char *line, t_obj_vectors *vec, t_scene *scene, int mat_id);
int	parse_uv(const char *line, t_vector *uv_vec);
int	parse_mtllib(const char *line, t_scene *scene);
int	apply_mtl(const char *line, t_scene *scene, int *mat_id);
int	gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color);

int	parse_obj_type(const char *line, t_scene *scene, t_vec3 *pos, t_obj_vectors *vec)
{
	t_obj			type;
	int				ret_val;
	static int		mat_id = -1;

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	if (mat_id == -1)
	{
		t_rgb_int rgbb = rgb_int(255, 255, 0);
		mat_id = gen_mat_by_color(vec->mat, vec->tex, &rgbb);
	}
	type = get_obj_type(line);
	ret_val = 0;
	if (type == mtllib)
		ret_val = parse_mtllib(line, scene);
	else if (type == usemtl)
		ret_val = apply_mtl(line, scene, &mat_id);
	else if (type == v)
		ret_val = parse_vertex(line, &vec->vertex, pos);
	else if (type == vn)
		ret_val = parse_normal(line, &vec->normal);
	else if (type == f)
		ret_val = parse_face(line, vec, scene, 0);
	else if (type == vt)
		ret_val = parse_uv(line, &vec->uv);
	return (ret_val);
}
