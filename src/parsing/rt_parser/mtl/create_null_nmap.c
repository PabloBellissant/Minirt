/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_null_nmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 22:39:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_null_nmap(t_vector *vec)
{
	int			tex_id;
	t_rgb_int	rgb;
	t_texture	*tex;

	rgb = rgb_int(255, 128, 128);
	tex_id = create_color_texture(vec, &rgb);
	if (tex_id == -1)
		return (-1);
	tex = get_vector_value(vec, tex_id);
	tex->name = ft_strdup("no_nmap");
	if (!tex->name)
		return (-1);
	return (tex_id);
}
