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

t_texture	*create_null_roughness(t_vector *vec)
{
	t_texture			*tex;

	tex = create_binary_texture(vec, 16);
	if (!tex)
		return (NULL);
	tex->name = ft_strdup("no_roughness");
	if (!tex->name)
		return (NULL);
	return (tex);
}
