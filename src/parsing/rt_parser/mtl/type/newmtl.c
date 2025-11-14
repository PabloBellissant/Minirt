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

int	base_mat(t_mat *mat, t_scene *scene);

#define NEWMTL_FORMAT " *newmtl  *%s *\n"

int	newmtl(const char *line, t_scene *scene)
{
	t_mat	*mat;

	mat = create_mat(&scene->mat);
	if (!mat)
		return (-1);
	if (ft_scan(0, NEWMTL_FORMAT, line, &mat->name) == -1)
		return (-1);
	return (base_mat(mat, scene));
}

int	get_nmap(t_scene *scene, char *nmap_name);
int	get_roughness(t_scene *scene, char *roughness_name);
int	get_ambient(t_scene *scene, char *ambient_name);

int	base_mat(t_mat *mat, t_scene *scene)
{
	mat->normal_id = get_nmap(scene, "null");
	if (mat->normal_id == -1)
		return (-1);
	mat->roughness_id = get_roughness(scene, "null");
	if (mat->roughness_id == -1)
		return (-1);
	mat->ambient_id = get_ambient(scene, "null");
	if (mat->ambient_id == -1)
		return (-1);
	return (0);
}
