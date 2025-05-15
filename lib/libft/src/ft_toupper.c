/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:27:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:24 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Take a character 'c' and uppercase it.
 * @param c the character
 * @return The character in uppercase.
 * @note If the entered character isn't in lowercase, the function
 * simply return the entered character.
 * @author Bellissant Pablo
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - LOWER_UPPER_VAL);
	return (c);
}
