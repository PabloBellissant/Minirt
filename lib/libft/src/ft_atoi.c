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

/**
 * @brief Convert a string to an integer.
 * @param nptr The string to convert.
 * @return The resulted integer.
 * @author Bellissant Pablo
 */
int	ft_atoi(const char *nptr)
{
	return ((int) ft_atol(nptr));
}
