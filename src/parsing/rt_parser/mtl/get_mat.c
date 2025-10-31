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

t_mat	*gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color);

t_mat	*get_mat(const char *mat_name, t_scene *scene, t_rgb_int *color)
{
	size_t	i;
	t_mat	*actual;

	if (!mat_name || *mat_name == 0)
		return (gen_mat_by_color(&scene->mat, &scene->texture, color));
	actual = scene->mat.data;
	i = 0;
	while (i < scene->mat.num_elements)
	{
		if (ft_strcmp(mat_name, actual[i].name) == 0)
			return (&actual[i]);
		++i;
	}
	return (NULL);
}

t_mat	*gen_mat_by_color(t_vector *mat, t_vector *tex, t_rgb_int *color)
{
	t_mat	*new;

	new = create_mat(mat);
	if (!new)
		return (NULL);
	*new = create_default_mat();
	new->kd_map = create_color_texture(tex, color);
	new->normal_map = create_null_nmap(tex);
	new->roughness_map = create_null_roughness(tex);
	new->ambient_map = create_null_ambient(tex);
	if (!new->kd_map || !new->normal_map || !new->roughness_map || !new->ambient_map)
		return (NULL);
	return (new);
}
