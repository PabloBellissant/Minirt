/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:29:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:39:47 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parsing.h"
#include "rt_xcerrcal.h"

t_object_type	get_type(const char *line)
{
	static const char	*elem[] = {"A", "C", "L", "sp", "pl",
		"obj", "sky", "mtl", NULL};
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
				return ((t_object_type)i + 1);
		}
		++i;
	}
	register_complex_err_msg(RT_E_MSG_UNDEFINED_TYPE, *line);
	error(pack_err(RT_ID, RT_E_UNDEFINED_TYPE), FL, LN, FC);
	return (UNDEFINED);
}
