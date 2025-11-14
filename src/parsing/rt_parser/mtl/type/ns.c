/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ns.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:55:17 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:00:41 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define NS_FORMAT " *Ns  *%f *\n"

int	ns(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, NS_FORMAT, line, &mat->ns) == -1)
		return (-1);
	if (mat->ns < 50.0f)
		mat->ns = 50.0f;
	return (0);
}
