/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:04:08 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/12 03:24:24 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define PM_FORMAT " *Pm  *%f[1] *\n"

int	pm(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, PM_FORMAT, line, &mat->pm) == -1)
		return (-1);
	return (0);
}
