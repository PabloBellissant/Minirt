/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:23:11 by pabellis          #+#    #+#             */
/*   Updated: 2025/03/06 03:23:13 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Calculate the average of two values.
 * @param val_a The first value.
 * @param val_b The second value.
 * @return The average in int.
 * @author Bellissant Pablo
 */
int	av(const int val_a, const int val_b)
{
	return ((val_a + val_b + 1) >> 1);
}
