/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:03:56 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/03/13 19:19:38 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, int c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] == c)
			|| (str[i] != c && str[i + 1] == 0))
		{
			words++;
		}
		i++;
	}
	return (words);
}

static int	copy(char **tab, const char *s, int sep)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep)
		{
			tab[j] = ft_strcrop(&s[i], sep);
			if (!tab[j])
				return (0);
			j++;
			while (s[i] != sep && s[i])
				i++;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(const char *str, int c)
{
	int		words;
	char	**res;

	if (!str)
		return (NULL);
	words = ft_count_words(str, c);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!copy(res, str, c))
		return (free_strr(res), NULL);
	return (res);
}
