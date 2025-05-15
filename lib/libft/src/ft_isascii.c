/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:53:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:51 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Know if a character is ascii or not
 * @param c the character to know.
 * @return 1 if the character is ascii, 0 otherwise.
 * @author Bellissant Pablo
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
