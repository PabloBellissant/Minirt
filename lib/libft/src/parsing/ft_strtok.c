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
