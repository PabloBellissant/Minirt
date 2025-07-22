/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 03:25:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/12 03:34:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

/**
 * @brief Joins multiple strings into a single one.
 * @param str The first string to join.
 * @param ... Additionals strings to join.
 * @return The new allocated string, or NULL if alloc fail.
 * @warning The returned array must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	*ft_strsjoin(char *str, ...)
{
	va_list		list;
	t_vector	vec;
	size_t		len_str;

	vector_init(&vec, sizeof(char));
	va_start(list, str);
	while (str != NULL)
	{
		len_str = ft_strlen(str);
		if (vector_add(&vec, str, len_str) == -1)
		{
			va_end(list);
			free_vector(&vec);
			return (NULL);
		}
		str = va_arg(list, char *);
	}
	va_end(list);
	if (vector_add(&vec, "\0", 1) == -1)
		free_vector(&vec);
	return (vec.data);
}
