/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mtl_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:31:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 04:31:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_mtl	get_mtl_type(const char *line)
{
	static const char	*elem[] = {"newmtl", "Ns", "Ka", "Kd", "Ks",
			"map_Kd", NULL};
	int			i;

	while (*line == ' ' || *line == '\t')
		++line;
	i = 0;
	while (elem[i])
	{
		if (ft_strncmp(elem[i], line, ft_strlen(elem[i])) == 0)
		{
			if ((*(line + ft_strlen(elem[i])) == ' ')
				|| (*(line + ft_strlen(elem[i])) == '\t'))
			{
				return ((t_mtl) i + 1);
			}
		}
		++i;
	}
	return (no_mtl);
}
