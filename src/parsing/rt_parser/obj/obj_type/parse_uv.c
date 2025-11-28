/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:22:22 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:22:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define UV_FORMAT " *vt  *%f *%f *"

int	parse_uv(const char *line, t_vector *uv_vec)
{
	t_vec2	uv;

	if (ft_scan(0, UV_FORMAT, line, &uv.x, &uv.y))
		return (-1);
	if (vector_add(uv_vec, &uv, 1) == -1)
		return (-1);
	return (0);
}
