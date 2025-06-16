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

#include "libft.h"

bool	is_above_int(char *value_in_str)
{
	long	long_value;
	int		count;

	if (!value_in_str || !*value_in_str)
		return (false);
	while (value_in_str[0] == '-' && value_in_str[1] == '0')
	{
		value_in_str[1] = '-';
		++value_in_str;
	}
	while (value_in_str[0] == '0' && value_in_str[1])
		++value_in_str;
	count = 0;
	while (ft_isdigit(value_in_str[count]))
	{
		++count;
		if (count > 10)
			return (true);
	}
	long_value = ft_atol(value_in_str);
	if (long_value > 2147483647 || long_value < -2147483648)
		return (true);
	return (false);
}
