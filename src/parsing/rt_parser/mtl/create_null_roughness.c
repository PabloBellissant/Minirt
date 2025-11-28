/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_null_roughness.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 22:39:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_null_roughness(t_vector *vec)
{
	t_texture	*tex;
	int			tex_id;

	tex_id = create_binary_texture(vec, 16);
	if (tex_id == -1)
		return (-1);
	tex = get_vector_value(vec, tex_id);
	tex->name = ft_strdup("no_roughness");
	if (!tex->name)
		return (-1);
	return (tex_id);
}
