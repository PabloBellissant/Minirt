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
	float	pm;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, PM_FORMAT, line, &pm) == -1)
		return (-1);
	mat->metalness_id = create_gray_level_texture(&scene->texture, pm * 255);
	if (mat->metalness_id == -1)
		return (-1);
	return (0);
}
