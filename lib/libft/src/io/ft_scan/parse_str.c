/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:14:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/29 06:15:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*parse_str(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		++i;
	return (ft_strndup(line, i));
}
