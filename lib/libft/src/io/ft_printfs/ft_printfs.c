/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:28:03 by jaubry--          #+#    #+#             */
/*   Updated: 2025/05/14 08:22:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfs_utils.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	size_t	i;
	size_t	write_len;

	i = 0;
	write_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			write_len += handler(args, format[++i], fd);
		else
			write_len += ft_putchar(format[i], fd);
		i++;
	}
	va_end(args);
	return (write_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	size_t	write_len;
	int		fd;

	fd = 1;
	i = 0;
	write_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			write_len += handler(args, format[++i], fd);
		else
			write_len += ft_putchar(format[i], fd);
		i++;
	}
	va_end(args);
	return (write_len);
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	va_list	args;
	size_t	i;
	size_t	write_len;

	i = 0;
	write_len = 0;
	va_copy(args, ap);
	while (format[i])
	{
		if (format[i] == '%')
			write_len += handler(args, format[++i], fd);
		else
			write_len += ft_putchar(format[i], fd);
		i++;
	}
	va_end(args);
	return (write_len);
}
