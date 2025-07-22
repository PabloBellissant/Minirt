/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:41:21 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:14 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Applies the function f to each character of the string s, passing 
 * its index as the first argument and the character itself as the second. 
 * A new string is created to collect the results from the successive 
 * applications of f.
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return The string created from the successive applications of ’f’.
 * NULL if the allocation fails.
 * @attention The f function must not be NULL.
 * @author Bellissant Pablo
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*newstring;

	newstring = ft_strdup(s);
	if (!newstring)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i += 1;
	}
	newstring[i] = 0;
	return (newstring);
}
