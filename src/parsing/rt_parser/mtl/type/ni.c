/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ni.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:04:08 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/12 03:18:26 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define NI_FORMAT " *Ni  *%f[1,5] *\n"

int	ni(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, NI_FORMAT, line, &mat->ni) == -1)
		return (-1);
	return (0);
}
