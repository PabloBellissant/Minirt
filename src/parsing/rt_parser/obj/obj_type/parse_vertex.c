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

int	parse_vertex(const char *line, t_vector *vertex, t_vec3 *scale)
{
	t_vertex	v;

	if (ft_scan(0, VERTEX_FORMAT, line, &v.pos.x, &v.pos.y, &v.pos.z))
		return (-1);
	v.pos = vec3_mult(v.pos, *scale);
	if (vector_add(vertex, &v, 1) == -1)
		return (-1);
	return (0);
}
