/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:57:15 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/06 18:57:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_next_word(char *s, const char *delim);

/**
 * @brief Tokenize a string using given delimiters (reentrant version).
 * Similar to `ft_strtok`, but safe for concurrent use.
 * This version should be used when parallel tokenization is needed.
 * @param s The input string to tokenize (or NULL for continuing).
 * @param delim A string containing delimiter characters.
 * @param str A pointer to a char* used
 * internally to keep context between calls.
 * @return A pointer to the next token, or NULL if no more tokens are found.
 * @author Bellissant Pablo
 */
char	*ft_strtok_r(char *s, const char *delim, char **str)
{
	char	*rvalue;

	if (s)
	{
		*str = s;
		while (**str && ft_strchr(delim, **str) != NULL)
			++(*str);
		if (**str == '\0')
			return (NULL);
	}
	if (!*str || **str == '\0')
		return (NULL);
	rvalue = *str;
	*str = get_next_word(*str, delim);
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
