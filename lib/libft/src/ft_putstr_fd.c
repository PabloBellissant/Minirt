/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:25:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:05 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 * @return -1 if write fail, 0 instead.
 * @author Bellissant Pablo
 */
int	ft_putstr_fd(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}
