/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 07:17:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/22 07:17:53 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return the gap between 2 values
 * @param value_a The first value.
 * @param value_b The second value.
 * @note ft_gap(3, 5): 2
 * @note ft_gap(-4, 1): 5
 * @return The gap between the 2 values.
 * @author Bellissant Pablo
 */
size_t	ft_gap(const ssize_t value_a, const ssize_t value_b)
{
	if ((value_a >= 0 && value_b >= 0) || (value_a < 0 && value_b < 0))
		return (ft_abs(value_a - value_b));
	if (value_a > value_b)
		return (value_a + ft_abs(value_b));
	return (value_b + ft_abs(value_a));
}
