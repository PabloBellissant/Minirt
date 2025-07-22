/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:50:09 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:55:35 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

static bool	ft_in(const char *set, const char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static size_t	ft_trimlen(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	while (s1[len - i - 1] && len)
	{
		if (!ft_in(set, s1[len - i - 1]))
			break ;
		i++;
	}
	return (len - i);
}

/*
	Functions that returns a pointer to the first character of s1 not in set
*/
static char	const	*ft_trimstart(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_in(set, s1[i]))
		i++;
	return (&s1[i]);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		i;
	size_t		trimlen;
	char		*r;
	const char	*start;

	i = 0;
	start = ft_trimstart(s1, set);
	trimlen = ft_trimlen(start, set);
	r = ft_calloc(sizeof(char), (trimlen + 1));
	if (!r)
		return (NULL);
	while (i < trimlen)
	{
		r[i] = start[i];
		i++;
	}
	return (r);
}
