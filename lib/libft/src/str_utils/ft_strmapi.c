/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:35:07 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:55:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	i;
	size_t	len;

	if (!f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	r = ft_calloc(sizeof(char), (len + 1));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	return (r);
}
