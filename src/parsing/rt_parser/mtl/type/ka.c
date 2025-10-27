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

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KA_FORMAT, line, &mat->ka.r, &mat->ka.g, &mat->ka.b) == -1)
		return (-1);
	return (0);
}
