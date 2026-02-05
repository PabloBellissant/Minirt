/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ka.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:00:36 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:00:44 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define KA_FORMAT " *Ka  *%f[1]  *%f[1]  *%f[1] *\n"

int	ka(const char *line, t_scene *scene)
{
	t_mat	*mat;
	t_rgb	ka;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KA_FORMAT, line, &ka.x, &ka.y, &ka.z) == -1)
		return (-1);
	mat->ambient_id.index = create_gray_level_texture(&scene->texture, 255);
	if (mat->ambient_id.index == -1)
		return (-1);
	return (0);
}
