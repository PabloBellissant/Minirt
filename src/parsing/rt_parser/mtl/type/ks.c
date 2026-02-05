/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ks.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:06:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:06:54 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define KS_FORMAT " *Ks  *%f[1]  *%f[1]  *%f[1] *\n"

int	ks(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KS_FORMAT, line, &mat->ks.x, &mat->ks.y, &mat->ks.z) == -1)
		return (-1);
	return (0);
}
