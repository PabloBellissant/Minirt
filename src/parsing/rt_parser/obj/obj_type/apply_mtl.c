/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mtl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:41:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 20:41:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

#define USEMTL_FORMAT " *usemtl  *%s *\n"

int	apply_mtl(const char *line, t_scene *scene, t_mat **actual_mtl)
{
	char	*mat_name;

	if (ft_scan(0, USEMTL_FORMAT, line, &mat_name))
		return (-1);
	*actual_mtl = get_mat(mat_name, &scene->mat);
	if (!*actual_mtl)
		return (-1);
	return (0);
}
