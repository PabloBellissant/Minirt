/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:42:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:06 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	beforecharset(const char *str, char c);
static size_t	ft_countwords(const char *str, char c);
static void		*free_error(char **tab, int wordplace);

/**
 * @brief Allocates and returns an array of strings obtained by splitting 
 * ’s’ using the character ’c’ as a delimiter.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return a NULL-terminated array of strings.
 * @note The returned array of strings must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	wordsnumber;
	size_t	wordplace;
	char	**output;

	wordsnumber = ft_countwords(s, c);
	output = malloc(sizeof(char *) * (wordsnumber + 1));
	if (!output)
		return (NULL);
	wordplace = 0;
	while (wordplace < wordsnumber)
	{
		while (*s == c)
			s += 1;
		output[wordplace] = ft_calloc(beforecharset(s, c) + 1, sizeof(char));
		if (!output[wordplace])
			return (free_error(output, wordplace));
		i = 0;
		while (i++ < beforecharset(s, c))
			output[wordplace][i - 1] = s[i - 1];
		s += i;
		wordplace += 1;
	}
	output[wordsnumber] = (char *)0;
	return (output);
}

/**
 * @brief Calculate the length of a string, 
 * before hitting the c character in the string.
 * @param str The string to look at.
 * @param c The character.
 * @note The function act like ft_strlen if there is no char c in the string.
 * @return The number of character before 'c' or '\0'.
 * @author Bellissant Pablo
 */
static size_t	beforecharset(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

/**
 * @brief Count the number of word, with the char c as delimiter.
 * @param str The string to count words.
 * @param c The delimiter character.
 * @return the number of words found.
 * @author Bellissant Pablo
 */
static size_t	ft_countwords(const char *str, char c)
{
	size_t	counter;

	counter = 0;
	while (str[0] == c && str[0])
		str += 1;
	while (str[0])
	{
		if (str[0] != c)
			counter += 1;
		while (str[0] != c && str[0])
			str += 1;
		while (str[0] == c && str[0])
			str += 1;
	}
	return (counter);
}

/**
 * This function is only used by ft_split, to free if there is an error.
 */
static void	*free_error(char **tab, int wordplace)
{
	while (wordplace >= 0)
	{
		free(tab[wordplace]);
		wordplace -= 1;
	}
	free(tab);
	return (NULL);
}
