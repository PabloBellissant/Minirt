/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_above_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 03:00:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/18 03:00:27 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

bool	is_above_int(char *value_in_str)
{
	size_t	value_len;
	int		int_value;

	if (!value_in_str || !*value_in_str)
		return (false);
	while (value_in_str[0] == '-' && value_in_str[1] == '0')
	{
		value_in_str[1] = '-';
		++value_in_str;
	}
	while (value_in_str[0] == '0' && value_in_str[1])
		++value_in_str;
	value_len = ft_strlen(value_in_str);
	int_value = ft_atoi(value_in_str);
	if (ft_getintlen(int_value) + 1 != value_len)
		return (true);
	return (false);
}
