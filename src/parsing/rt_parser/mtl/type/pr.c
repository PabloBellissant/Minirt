/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:58:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/24 00:58:45 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define PR_FORMAT " *Pr  *%f[1000] *\n"

int	pr(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, PR_FORMAT, line, &mat->pr) == -1)
		return (-1);
	mat->roughness_id = create_binary_texture(&scene->texture, fminf(mat->pr, 1.0f) * 255);
	if (mat->roughness_id == -1)
		return (-1);
	return (0);
}
