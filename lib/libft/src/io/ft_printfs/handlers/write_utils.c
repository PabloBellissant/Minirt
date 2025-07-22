/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:55:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/01 01:30:41 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfs_utils.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

ssize_t	ft_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t	ft_putstr(char *str, int fd)
{
	return (write(fd, str, ft_strlen(str)));
}

ssize_t	ft_putstr_l(char *str, size_t len, int fd)
{
	return (write(fd, str, len));
}

ssize_t	ft_printstr(char *str, int fd)
{
	if (!str)
		return (ft_putstr_l("(null)", 6, fd));
	else
		return (ft_putstr(str, fd));
}
