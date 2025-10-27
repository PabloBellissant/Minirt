/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:02:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:02:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define KD_FORMAT " *Kd  *%f[1]  *%f[1]  *%f[1] *\n"

int	kd(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KD_FORMAT, line, &mat->kd.r, &mat->kd.g, &mat->kd.b) == -1)
		return (-1);
	return (0);
}
