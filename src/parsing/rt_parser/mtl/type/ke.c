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

#define KE_FORMAT " *Ke  *%f[1000]  *%f[1000]  *%f[1000] *\n"

int	ke(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KE_FORMAT, line, &mat->ke.x, &mat->ke.y, &mat->ke.z) == -1)
		return (-1);
	return (0);
}
