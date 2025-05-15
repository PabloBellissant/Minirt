/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:21:02 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/31 20:08:19 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

/**
 * @brief Know if a string is a digit or not
 * @param str the string to know.
 * @return 1 if the string only contain digit, 0 otherwise.
 * @warning The str must not be NULL.
 * @author Bellissant Pablo
 */
int	ft_str_is_digit(const char *str)
{
	size_t	i;

	if ((str[0] == '-' || str[0] == '+') && ft_isdigit(str[1]) == 1)
		++str;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}
