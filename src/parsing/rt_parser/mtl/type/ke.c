/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ke.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 07:18:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/26 07:19:41 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define Ke_FORMAT " *Ke  *%f[10]  *%f[10]  *%f[10] *\n"

int	ke(const char *line, t_scene *scene)
{
	t_mat		*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, Ke_FORMAT, line, &mat->ke.r, &mat->ke.g, &mat->ke.b) == -1)
		return (-1);
	return (0);
}
