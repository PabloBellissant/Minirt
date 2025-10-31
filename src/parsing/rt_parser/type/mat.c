/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:32:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/24 00:32:07 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "rt_xcerrcal.h"
#include "parsing.h"

#define MATERIAL_FORMAT " *mat  *%s  *%f[1] *, *%f[1] *, *%f[1]  *%f[1] *,\
*%f[1] *, *%f[1]  *%f[1000]  *%f[1](  *%s  *%s  *%s  *%s  *%s) *\n"

t_texture	*get_kd(t_scene *scene, char *texture_name);
t_texture	*get_nmap(t_scene *scene, char *nmap_name);
t_texture	*get_roughness(t_scene *scene, char *nmap_name);
t_texture	*get_ambient(t_scene *scene, char *nmap_name);
t_texture	*get_opacity(t_scene *scene, char *nmap_name);
int			gen_map_by_mat(t_mat *mat, t_scene *scene);

int	mat(const char *line, int line_num, t_scene *scene)
{
	t_mat	*mat;
	char	*texture_name;
	char	*nmap_name;
	char	*roughness_name;
	char	*ambient_name;
	char	*opacity_name;

	mat = create_mat(&scene->mat);
	if (!mat)
		return (-1);
	if (ft_scan(line_num, MATERIAL_FORMAT, line, &mat->name,
		&mat->kd.r, &mat->kd.g, &mat->kd.b, &mat->ks.r, &mat->ks.g, &mat->ks.b,
		&mat->ns, &mat->opacity, &texture_name, &nmap_name, &roughness_name,
		&ambient_name, &opacity_name))
	{
		return (error(pack_err(RT_ID, RT_E_MAT), FL, LN, FC));
	}
	if (*texture_name)
	{
		mat->kd_map = get_kd(scene, texture_name);
		mat->normal_map = get_nmap(scene, nmap_name);
		mat->roughness_map = get_roughness(scene, roughness_name);
		mat->ambient_map = get_ambient(scene, ambient_name);
		mat->opacity_map = get_opacity(scene, opacity_name);
		if (!mat->kd_map || !mat->normal_map || !mat->roughness_map || !mat->ambient_map)
			return (-1);
	}
	else if (gen_map_by_mat(mat, scene) == -1)
		return (-1);
	return (0);
}

int	gen_map_by_mat(t_mat *mat, t_scene *scene)
{
	t_rgb_int	temp;

	temp = rgb_ftoi(mat->kd);
	mat->kd_map = create_color_texture(&scene->texture, &temp);
	mat->normal_map = get_nmap(scene, "null");
	mat->roughness_map = get_roughness(scene, "null");
	mat->ambient_map = get_ambient(scene, "null");
	mat->opacity_map = create_binary_texture(&scene->texture, (int)(mat->opacity * 255));
	if (!mat->kd_map || !mat->normal_map || !mat->roughness_map || !mat->ambient_map)
		return (-1);
	return (0);
}

t_texture	*get_kd(t_scene *scene, char *texture_name)
{
	t_texture	*tex;

	if (ft_strcmp(texture_name, "null") == 0)
	{
		tex = get_texture(scene, "no_tex");
		if (!tex)
			tex = create_null_texture(&scene->texture);
		return (tex);
	}
	tex = get_texture(scene, texture_name);
	return (tex);
}

t_texture	*get_nmap(t_scene *scene, char *nmap_name)
{
	t_texture	*tex;

	if (ft_strcmp(nmap_name, "null") == 0)
	{
		tex = get_texture(scene, "no_nmap");
		if (!tex)
			tex = create_null_nmap(&scene->texture);
		return (tex);
	}
	tex = get_texture(scene, nmap_name);
	return (tex);
}

t_texture	*get_roughness(t_scene *scene, char *nmap_name)
{
	t_texture	*tex;

	if (ft_strcmp(nmap_name, "null") == 0)
	{
		tex = get_texture(scene, "no_roughness");
		if (!tex)
			tex = create_null_roughness(&scene->texture);
		return (tex);
	}
	tex = get_texture(scene, nmap_name);
	return (tex);
}

t_texture	*get_ambient(t_scene *scene, char *nmap_name)
{
	t_texture	*tex;

	if (ft_strcmp(nmap_name, "null") == 0)
	{
		tex = get_texture(scene, "no_ambient");
		if (!tex)
			tex = create_null_ambient(&scene->texture);
		return (tex);
	}
	tex = get_texture(scene, nmap_name);
	return (tex);
}

t_texture	*get_opacity(t_scene *scene, char *nmap_name)
{
	t_texture	*tex;

	if (ft_strcmp(nmap_name, "null") == 0)
	{
		tex = get_texture(scene, "no_opacity");
		if (!tex)
			tex = create_null_opacity(&scene->texture);
		return (tex);
	}
	tex = get_texture(scene, nmap_name);
	return (tex);
}
