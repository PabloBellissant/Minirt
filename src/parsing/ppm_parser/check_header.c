/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 01:56:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/26 01:56:55 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*skip_comment(int fd);

int	check_header(const int fd, int *width, int *height, int *bit)
{
	char	*line;

	line = skip_comment(fd);
	if (!line || ft_scan(2, " *%d  *%d *\n", line, width, height) != 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	line = skip_comment(fd);
	if (!line || ft_scan(3, " *%d *\n", line, bit) != 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}
