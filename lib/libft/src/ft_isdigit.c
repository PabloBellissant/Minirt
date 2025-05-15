/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:23:09 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:56 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Know if a character is a digit or not
 * @param c the character to know.
 * @return 1 if the character is a digit, 0 otherwise.
 * @author Bellissant Pablo
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
