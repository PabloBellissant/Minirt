/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:05:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:57 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Know if a character is printable or not
 * @param c the character to know.
 * @return 1 if the character is printable, 0 otherwise.
 * @author Bellissant Pablo
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
