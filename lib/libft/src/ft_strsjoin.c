/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 03:25:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/28 03:25:37 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static void	ft_strcat_va(char *output, va_list list, size_t *total_len);

char	*ft_strsjoin(char *first, ...)
{
	va_list	list;
	size_t	total_len;
	char	*output;

	total_len = ft_strlen(first);
	va_start(list, first);
	output = malloc(sizeof(char) * (total_len + 1));
	if (!output)
		return (NULL);
	output[0] = '\0';
	ft_strlcat(output, first, total_len + 1);
	ft_strcat_va(output, list, &total_len);
	va_end(list);
	return (output);
}

static void	ft_strcat_va(char *output, va_list list, size_t *total_len)
{
	char	*str;

	str = va_arg(list, char *);
	while (str != NULL)
	{
		ft_strlcat(output, str, *total_len + ft_strlen(str) + 1);
		*total_len += ft_strlen(str);
		str = va_arg(list, char *);
	}
}
