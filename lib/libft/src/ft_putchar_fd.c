/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:15:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:03 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 * @return -1 if write fail, 0 instead.
 * @author Bellissant Pablo
 */
int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
