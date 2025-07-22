/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:37:51 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/01 01:31:00 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

/*
	Function that takes as parameter two strings and concatanates them.
	It always frees the first string.
*/
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (str);
}

char	*ft_strndup_gnl(char *str, size_t n)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (n == 0)
		n = ft_strlen(str);
	ret = ft_calloc(sizeof(char), (n + 1));
	if (!ret)
		return (NULL);
	while (str[i] && (i < n))
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
