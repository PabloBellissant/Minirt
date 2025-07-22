/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:58:10 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/01 01:30:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfs_utils.h"

static ssize_t	ft_recu_putnbr(long int nb, int fd)
{
	if (nb > 0)
		return (ft_recu_putnbr(nb / 10, fd)
			+ ft_putchar((nb % 10) + '0', fd));
	return (0);
}

ssize_t	ft_putnbr(long int nb, int fd)
{
	ssize_t		write_len;

	write_len = 0;
	if (nb < 0)
	{
		write_len += ft_putchar('-', fd);
		nb = -nb;
	}
	if (nb == 0)
		write_len += ft_putchar('0', fd);
	else
		write_len += ft_recu_putnbr(nb, fd);
	return (write_len);
}
