/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:54:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/01 01:30:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfs_utils.h"

ssize_t	handler(va_list args, char specifier, int fd)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_printstr(va_arg(args, char *), fd));
	else if (specifier == 'p')
		return (ft_put_ptr(va_arg(args, long unsigned), fd));
	else if ((specifier == 'd') || (specifier == 'i'))
		return (ft_putnbr(va_arg(args, int), fd));
	else if (specifier == 'u')
		return (ft_putnbr(va_arg(args, unsigned), fd));
	else if (specifier == 'x')
		return (ft_put_hex(va_arg(args, unsigned), false, fd));
	else if (specifier == 'X')
		return (ft_put_hex(va_arg(args, unsigned), true, fd));
	return (ft_putchar(specifier, fd));
}
