/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 02:12:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 09:37:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "minirt.h"
#include "rt_xcerrcal.h"

#define OBJ_FORMAT " *obj  *%s  *%f *, *%f *, *%f  *%f *, *%f *, *%f  *%f *,\
*%f *, *%f *\n"

int		parse_obj_file(int fd, t_scene *scene, t_vec3 *scale);
int		create_local_bvh(t_scene *scene, t_mesh *mesh);
void	fill_internal(t_mesh *mesh, t_vector *objects);
t_vec3	rotate_point(t_vec3 pos, t_vec3 rot);

int	obj(const char *line, int line_num, t_scene *scene)
{
	t_mesh	mesh;

	mesh.offset = scene->objects.num_elements;
	if (ft_scan(line_num, OBJ_FORMAT, line, &mesh.path,
			&mesh.pos.x, &mesh.pos.y, &mesh.pos.z,
			&mesh.rot.x, &mesh.rot.y, &mesh.rot.z,
			&mesh.scale.x, &mesh.scale.y, &mesh.scale.z))
	{
		free(mesh.path);
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	if (parse_obj_file(open(mesh.path, O_RDONLY), scene, &mesh.scale) == -1)
	{
		register_complex_err_msg(RT_E_MSG_OBJ_FAIL, mesh.path);
		return (error(pack_err(RT_ID, RT_E_OBJ_FAIL), FL, LN, FC));
	}
	mesh.triangle_count = scene->objects.num_elements - mesh.offset;
	fill_internal(&mesh, &scene->objects);
	if (scene->mesh.num_elements == 0)
		vector_init(&scene->mesh, sizeof(t_mesh));
	return (vector_add(&scene->mesh, &mesh, 1));
}

static inline void	pre_compute_triangle(t_triangle *tri)
{
	t_vec3	sum;

	tri->edge_p1p0 = vec3_sub(tri->p1.pos, tri->p0.pos);
	tri->edge_p2p0 = vec3_sub(tri->p2.pos, tri->p0.pos);
	tri->d00 = vec3_dot(tri->edge_p1p0, tri->edge_p1p0);
	tri->d01 = vec3_dot(tri->edge_p1p0, tri->edge_p2p0);
	tri->d11 = vec3_dot(tri->edge_p2p0, tri->edge_p2p0);
	tri->denom
		= tri->d00 * tri->d11 - tri->d01 * tri->d01;
	sum = vec3_add(tri->p0.pos, tri->p1.pos);
	sum = vec3_add(sum, tri->p2.pos);
	tri->centroid = vec3_div_scalar(sum, 3.0f);
}

void	fill_internal(t_mesh *mesh, t_vector *objects)
{
	size_t		i;
	t_triangle	*t;
	t_object	*obj;

	obj = objects->data;
	i = 0;
	while (i < mesh->triangle_count)
	{
		t = &obj[i + mesh->offset].triangle;
		t->p0.pos = vec3_mult(t->p0.pos, mesh->scale);
		t->p1.pos = vec3_mult(t->p1.pos, mesh->scale);
		t->p2.pos = vec3_mult(t->p2.pos, mesh->scale);
		t->p0.pos = rotate_point(t->p0.pos, mesh->rot);
		t->p1.pos = rotate_point(t->p1.pos, mesh->rot);
		t->p2.pos = rotate_point(t->p2.pos, mesh->rot);
		t->p0.norm = rotate_point(t->p0.norm, mesh->rot);
		t->p1.norm = rotate_point(t->p1.norm, mesh->rot);
		t->p2.norm = rotate_point(t->p2.norm, mesh->rot);
		t->p0.pos = vec3_add(t->p0.pos, mesh->pos);
		t->p1.pos = vec3_add(t->p1.pos, mesh->pos);
		t->p2.pos = vec3_add(t->p2.pos, mesh->pos);
		pre_compute_triangle(t);
		++i;
	}
}
