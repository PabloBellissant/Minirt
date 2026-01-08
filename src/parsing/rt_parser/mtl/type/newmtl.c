/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmtl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:45:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 04:45:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parsing.h"
#include "rt_xcerrcal.h"

#define NEWMTL_FORMAT " *newmtl  *%s *\n"

int	newmtl(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = create_mat(&scene->mat, &scene->texture);
	if (!mat)
		return (-1);
	if (ft_scan(0, NEWMTL_FORMAT, line, &mat->name) == -1)
		return (-1);
	return (0);
}

