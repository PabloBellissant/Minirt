/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:09:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:49 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static int				ft_checkoverflow(unsigned long val, int sign);
static int				ft_is_whitespace(int c);
static unsigned long	ft_number_in_str_len(const char *s);

/**
 * @brief Convert a string to an integer.
 * @param nptr A string that contain numeric characters.
 * @return an int that has been created by the function.
 * @note The returned integer can be negative or positive.
 * @author Bellissant Pablo
 */
int	ft_atoi(const char *nptr)
{
	unsigned long	i;
	unsigned long	final_val;
	int				check_negative;
	unsigned long	val_to_add;

	while (ft_is_whitespace(nptr[0]))
		nptr++;
	check_negative = 1;
	if (nptr[0] == '-')
		check_negative = -1;
	if (nptr[0] == '+' || nptr[0] == '-')
		nptr += 1;
	i = 0;
	final_val = 0;
	while (i < ft_number_in_str_len(nptr))
	{
		final_val *= 10;
		val_to_add = final_val + (nptr[i] - '0');
		if (ft_checkoverflow(val_to_add, check_negative) != 1)
			return (ft_checkoverflow(val_to_add, check_negative));
		final_val = val_to_add;
		i += 1;
	}
	return (final_val * check_negative);
}

/**
 * @brief counts the number of digits before another character in a string.
 * @param s the string to count digits from.
 * @return the number of digits in the string.
 * @attention the string must not be NULL.
 * @example "4242abc1234" -> 4242.
 * @author Bellissant Pablo
 */
static unsigned long	ft_number_in_str_len(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i += 1;
	return (i);
}

/**
 * @brief Know if a character is a whitespace or not.
 * @param c the character to know.
 * @return 1 if the character is a whitespace, 0 otherwise.
 * @author Bellissant Pablo
 */
static int	ft_is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

/**
 * This function is only used by ft_atoi function to reproduce 
 * the undified behavour of the real atoi() function.
 */
static int	ft_checkoverflow(unsigned long val, int sign)
{
	if (val > LLONG_MAX)
	{
		if (sign == -1)
			return (0);
		if (sign == 1)
			return (-1);
	}
	return (1);
}
