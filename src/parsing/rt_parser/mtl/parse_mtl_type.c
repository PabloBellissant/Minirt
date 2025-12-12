/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:40:26 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/12 03:19:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_mtl	get_mtl_type(const char *line);

int	parse_mtl_type(const char *line, t_scene *scene)
{
	t_mtl		type;
	static int	(*f[])(const char *, t_scene *)
		= {newmtl, ns, ka, kd, ks, map_kd, map_bump, map_pr, map_ka, map_d, d, ni, pr, ke, pm};

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_mtl_type(line);
	if (type == no_mtl)
		return (0);
	return (f[type - 1](line, scene));
}
