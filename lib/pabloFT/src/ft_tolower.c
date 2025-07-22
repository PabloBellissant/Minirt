/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:35:31 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:22 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Take a character 'c' and lowercase it.
 * @param c the character
 * @return The character in lowercase.
 * @note If the entered character isn't in uppercase, the function
 * simply return the entered character.
 * @author Bellissant Pablo
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + LOWER_UPPER_VAL);
	return (c);
}
