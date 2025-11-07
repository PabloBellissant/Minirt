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

int	get_kd(t_scene *scene, char *texture_name);
int	get_nmap(t_scene *scene, char *nmap_name);
int	get_roughness(t_scene *scene, char *roughness_name);
int	get_ambient(t_scene *scene, char *ambient_name);
int	get_opacity(t_scene *scene, char *opacity_name);
int	gen_map_by_mat(t_mat *mat, t_scene *scene);

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
		mat->kd_id = get_kd(scene, texture_name);
		mat->normal_id = get_nmap(scene, nmap_name);
		mat->roughness_id = get_roughness(scene, roughness_name);
		mat->ambient_id = get_ambient(scene, ambient_name);
		mat->opacity_id = get_opacity(scene, opacity_name);
		if (mat->kd_id == -1 || mat->normal_id == -1 || mat->roughness_id == -1
			|| mat->ambient_id == -1 || mat->opacity_id == -1)
		{
			return (-1);
		}
	}
	else if (gen_map_by_mat(mat, scene) == -1)
		return (-1);
	return (0);
}

int	gen_map_by_mat(t_mat *mat, t_scene *scene)
{
	t_rgb_int	temp;

	temp = rgb_ftoi(mat->kd);
	mat->kd_id = create_color_texture(&scene->texture, &temp);
	mat->normal_id = get_nmap(scene, "null");
	mat->roughness_id = get_roughness(scene, "null");
	mat->ambient_id = get_ambient(scene, "null");
	mat->opacity_id = create_binary_texture(&scene->texture, (int)(mat->opacity * 255));
	if (mat->kd_id == -1 || mat->normal_id == -1 || mat->roughness_id == -1
		|| mat->ambient_id == -1 || mat->opacity_id == -1)
	{
		return (-1);
	}
	return (0);
}

int	get_kd(t_scene *scene, char *texture_name)
{
	int	tex_id;

	if (ft_strcmp(texture_name, "null") == 0)
	{
		tex_id = get_texture(scene, "no_tex");
		if (tex_id == -1)
			tex_id = create_null_texture(&scene->texture);
		return (tex_id);
	}
	tex_id = get_texture(scene, texture_name);
	return (tex_id);
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
	return (tex_id);
}

int	get_opacity(t_scene *scene, char *opacity_name)
{
	int	tex_id;

	if (ft_strcmp(opacity_name, "null") == 0)
	{
		tex_id = get_texture(scene, "no_opacity");
		if (tex_id == -1)
			tex_id = create_null_opacity(&scene->texture);
		return (tex_id);
	}
	tex_id = get_texture(scene, opacity_name);
	return (tex_id);
}
