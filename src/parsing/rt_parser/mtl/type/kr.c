/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:37:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/13 17:37:50 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define KR_FORMAT " *Kr  *%f[1] *\n"

int	kr(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, KR_FORMAT, line, &mat->kr) == -1)
		return (-1);
	return (0);
}
