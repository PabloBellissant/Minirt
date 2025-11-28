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

int	get_nmap(t_scene *scene, char *nmap_name)
{
	int	tex_id;

	if (ft_strcmp(nmap_name, "null") == 0)
	{
		tex_id = get_texture(scene, "no_nmap");
		if (tex_id == -1)
			tex_id = create_null_nmap(&scene->texture);
		return (tex_id);
	}
	tex_id = get_texture(scene, nmap_name);
	if (tex_id == -1)
	{
		register_complex_err_msg(RT_E_MSG_UNKNOW_NMAP, nmap_name);
		return (error(pack_err(RT_ID, RT_E_UNKNOW_NMAP), FL, LN, FC));
	}
	return (tex_id);
}

int	get_roughness(t_scene *scene, char *roughness_name)
{
	int	tex_id;

	if (ft_strcmp(roughness_name, "null") == 0)
	{
		tex_id = get_texture(scene, "no_roughness");
		if (tex_id == -1)
			tex_id = create_null_roughness(&scene->texture);
		return (tex_id);
	}
	tex_id = get_texture(scene, roughness_name);
	if (tex_id == -1)
	{
		register_complex_err_msg(RT_E_MSG_UNKNOW_ROUGHNESS, roughness_name);
		return (error(pack_err(RT_ID, RT_E_UNKNOW_ROUGHNESS), FL, LN, FC));
	}
	return (tex_id);
}

int	get_ambient(t_scene *scene, char *ambient_name)
{
	int	tex_id;

	if (ft_strcmp(ambient_name, "null") == 0)
	{
		tex_id = get_texture(scene, "no_ambient");
		if (tex_id == -1)
			tex_id = create_null_ambient(&scene->texture);
		return (tex_id);
	}
	tex_id = get_texture(scene, ambient_name);
	if (tex_id == -1)
	{
		register_complex_err_msg(RT_E_MSG_UNKNOW_AMBIENT, ambient_name);
		return (error(pack_err(RT_ID, RT_E_UNKNOW_AMBIENT), FL, LN, FC));
	}
	return (tex_id);
}


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
	mat->opacity_id = get_ambient(scene, "null");
	if (mat->opacity_id == -1)
		return (-1);
	return (0);
}
