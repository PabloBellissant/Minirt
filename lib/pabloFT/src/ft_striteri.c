/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:51:02 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:09 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief  Applies the function ’f’ on each character of the string passed 
 * as argument, passing its index as first argument. Each character is 
 * passed by address to ’f’ to be modified if necessary.
 * @param s The string on which to iterate.
 * @param f  The function to apply to each character.
 * @warning the f function must not be NULL.
 * @author Bellissant Pablo
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		++i;
	}
}
