/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:04:44 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 21:04:45 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color);

int	get_mat(const char *mat_name, t_scene *scene, t_rgb_int *color)
{
	size_t	i;
	t_mat	*actual;

	if (!mat_name || *mat_name == 0)
		return (gen_mat_by_color(&scene->mat, &scene->texture, color));
	actual = scene->mat.data;
	i = 0;
	while (i < scene->mat.num_elements)
	{
		if (actual[i].name && ft_strcmp(mat_name, actual[i].name) == 0)
			return ((int) i);
		++i;
	}
	return (-1);
}

int	gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color)
{
	t_mat	*new;

	new = create_mat(mat);
	if (!new)
		return (-1);
	*new = create_default_mat();
	new->kd_id = create_color_texture(tex, color);
	new->normal_id = create_null_nmap(tex);
	new->roughness_id = create_null_roughness(tex);
	new->ambient_id = create_null_ambient(tex);
	new->opacity_id = create_null_opacity(tex);
	if (new->kd_id == -1 || new->normal_id == -1 || new->roughness_id == -1
		|| new->ambient_id == -1 || new->opacity_id == -1)
	{
		return (-1);
	}
	return ((int) mat->num_elements - 1);
}
