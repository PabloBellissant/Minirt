/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:29:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 14:52:39 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parsing.h"

static void	print_unrecognized_identifier(char *token, int actual_line);

t_object_type	get_type(char *line, int actual_line)
{
	static char	*elem[] = {"A", "C", "L", "sp", "pl", "cy", NULL};
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
				return (i + 1);
		}
		++i;
	}
	print_unrecognized_identifier(line, actual_line);
	return (UNDEFINED);
}

static void	print_unrecognized_identifier(char *token, int actual_line)
{
	int	len;

	len = 0;
	while (token[len] && (token[len] != ' ' && token[len] != '\n'))
		++len;
	ft_putstr_fd("Error\nUnrecognized identifier : '", 2);
	write(2, token, len);
	ft_putstr_fd("', line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	write(2, "'\n", 2);
}
