/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:44:00 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/10 19:21:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, bool is_char(char))
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((!is_char(str[i]) && is_char(str[i + 1]))
			|| (!is_char(str[i]) && str[i + 1] == 0))
			words++;
		i++;
	}
	return (words);
}

static char	*strcrop(const char *str, bool is_char(char))
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && !is_char(str[i]))
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = str[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

static int	copy(char **tab, const char *s, bool is_char(char))
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (!is_char(s[i]))
		{
			tab[j] = strcrop(&s[i], is_char);
			if (!tab[j])
				return (0);
			j++;
			while (!is_char(s[i]) && s[i])
				i++;
		}
		else
			i++;
	}
	return (1);
}

char	**split_by_char(const char *str, bool is_char(char))
{
	int		words;
	char	**res;

	if (!str)
		return (NULL);
	words = ft_count_words(str, is_char);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!copy(res, str, is_char))
		return (free_strr(res), NULL);
	return (res);
}
