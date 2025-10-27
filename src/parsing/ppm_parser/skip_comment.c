/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 01:46:14 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 01:46:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_by_char(int fd);

char	*skip_comment(const int fd)
{
	char *line;

	line = read_by_char(fd);
	while (line)
	{
		if (line[0] != '#')
			return (line);
		free(line);
		line = read_by_char(fd);
	}
	return (NULL);
}

static char	*read_by_char(const int fd)
{
	t_vector	vec;
	char		read_char;

	if (read(fd, &read_char, 1) == -1)
		return (NULL);
	vector_init(&vec, sizeof(char));
	while (read_char != '\n')
	{
		if (vector_add(&vec, &read_char, 1) == -1)
		{
			free(vec.data);
			return (NULL);
		}
		if (read(fd, &read_char, 1) == -1)
		{
			free(vec.data);
			return (NULL);
		}
	}
	return (vec.data);
}
