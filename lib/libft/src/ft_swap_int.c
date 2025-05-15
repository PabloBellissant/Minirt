/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:39:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/04 23:55:53 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/**
 * @brief Swap the 2 entered integers.
 * @param val1 The first val.
 * @param val1 The second val.
 * @author Bellissant Pablo
 */
void	swap_int(int *val1, int *val2)
{
	int	temp;

	temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}
