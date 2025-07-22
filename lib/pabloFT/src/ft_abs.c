/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:22:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/21 01:22:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Convert integer to is absolute value.
 * @param value the integer to get absolute value from.
 * @return the absolute value of n.
 * @author Bellissant Pablo
 */
size_t	ft_abs(const ssize_t value)
{
	if (value < 0)
		return (-value);
	return (value);
}
