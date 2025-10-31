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

t_texture	*create_null_nmap(t_vector *vec)
{
	t_texture	*tex;
	t_rgb_int	rgb;

	rgb = rgb_int(255, 128, 128);
	tex = create_color_texture(vec, &rgb);
	if (!tex)
		return (NULL);
	tex->name = ft_strdup("no_nmap");
	if (!tex->name)
		return (NULL);
	return (tex);
}
