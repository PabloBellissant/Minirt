/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:20:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:20:44 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define NORMAL_FORMAT " *vn  *%f *%f *%f *"

int	parse_normal(const char *line, t_vector *normal_vec)
{
	t_vec3	normal;

	if (ft_scan(0, NORMAL_FORMAT, line, &normal.x, &normal.y, &normal.z))
		return (-1);
	if (vector_add(normal_vec, &normal, 1) == -1)
		return (-1);
	return (0);
}
