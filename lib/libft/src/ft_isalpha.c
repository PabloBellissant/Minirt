/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:23:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:51 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Know if a character is alphabetic or not
 * @param c the character to know.
 * @return 1 if the character is alphabetic, 0 otherwise.
 * @author Bellissant Pablo
 */
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
