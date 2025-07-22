/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:00:22 by pabellis          #+#    #+#             */
/*   Updated: 2025/03/18 00:00:25 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_next_word(char *s, const char *delim);

/**
 * @brief Tokenize a string using delimiters.
 * Splits the string `s` into tokens separated characters in `delim`.
 * @param s The input string to tokenize (or NULL for continuing).
 * @param delim A string containing delimiter characters.
 * @example On the first call, provide `s` with the string to tokenize.
 * On subsequent calls, pass `NULL` to continue tokenizing the same string.
 * @return A pointer to the next token, or NULL if no more tokens are found.
 * @author Bellissant Pablo
 */
char	*ft_strtok(char *s, const char *delim)
{
	static char	*str = NULL;
	char		*rvalue;

	if (s)
	{
		str = s;
		while (*str && ft_strchr(delim, *str) != NULL)
			++str;
		if (*str == '\0')
			return (NULL);
	}
	if (!str)
		return (NULL);
	rvalue = str;
	str = get_next_word(str, delim);
	return (rvalue);
}

static char	*get_next_word(char *s, const char *delim)
{
	while (*s && ft_strchr(delim, *s) == NULL)
		++s;
	while (*s && ft_strchr(delim, *s) != NULL)
	{
		*s = '\0';
		++s;
	}
	if (*s == '\0')
		return (NULL);
	return (s);
}
