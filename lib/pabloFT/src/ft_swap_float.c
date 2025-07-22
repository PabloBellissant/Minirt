/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_float.                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:39:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/04 23:55:53 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/**
 * @brief Swap the 2 entered float.
 * @param val1 The first val.
 * @param val1 The second val.
 * @author Bellissant Pablo
 */
void	swap_float(float *val1, float *val2)
{
	float	temp;

	temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}
