/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:11:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:05 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 * @return -1 if write fail, 0 instead.
 * @author Bellissant Pablo
 */
int	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == INT_MIN)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return (-1);
		return (0);
	}
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		n = -n;
	}
	if (n >= 10)
		if (ft_putnbr_fd(n / 10, fd) == -1)
			return (-1);
	c = (n % 10) + '0';
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
