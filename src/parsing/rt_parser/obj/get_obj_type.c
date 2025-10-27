/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:29:08 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:29:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	get_obj_type(const char *line)
{
	static const char	*elem[] = {"mtllib", "usemtl", "vn", "vt",
			"v", "f", NULL};
	int					i;

	while (*line == ' ' || *line == '\t')
		++line;
	i = 0;
	while (elem[i])
	{
		if (ft_strncmp(elem[i], line, ft_strlen(elem[i])) == 0)
		{
			if ((*(line + ft_strlen(elem[i])) == ' ')
				|| (*(line + ft_strlen(elem[i])) == '\t'))
				return ((t_obj) i + 1);
		}
		++i;
	}
	return (null);
}
