/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:33:52 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:55:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[len - i - 1] == (char)c)
			return ((char *)(s + (len - 1 - i)));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + len));
	return (NULL);
}
