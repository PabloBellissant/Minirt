/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:30:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/11 19:30:34 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define D_FORMAT " *d  *%f[1] *\n"

int	d(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, D_FORMAT, line, &mat->opacity) == -1)
		return (-1);
	mat->opacity_id = create_gray_level_texture(&scene->texture,
		(int)(mat->opacity * 255));
	if (mat->opacity_id == -1)
		return (-1);
	return (0);
}
