/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:53:44 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 17:53:46 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define VERTEX_FORMAT " *v  *%f *%f *%f *"

t_vec3	rotate_point(t_vec3 pos, t_vec3 rot);

int	parse_vertex(const char *line, t_vector *vertex, t_pos_attribute *attr)
{
	t_vertex	v;

	if (ft_scan(0, VERTEX_FORMAT, line, &v.pos.x, &v.pos.y, &v.pos.z))
		return (-1);
	v.pos = vec3_mult(v.pos, attr->scale);
	v.pos = vec3_add(v.pos, attr->pos);
	v.pos = rotate_point(v.pos, attr->dir);
	v.norm = attr->dir;
	if (vector_add(vertex, &v, 1) == -1)
		return (-1);
	return (0);
}
