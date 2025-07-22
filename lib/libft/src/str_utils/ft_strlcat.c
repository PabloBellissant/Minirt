/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:28:08 by jaubry--          #+#    #+#             */
/*   Updated: 2024/08/27 13:53:56 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	j = 0;
	if ((size < dstlen) || !size)
		return (srclen + size);
	else
	{
		while (src[j] && (i < size))
			dst[i++] = src[j++];
		if ((i == size) && (dstlen < size))
			dst[i - 1] = '\0';
		else
			dst[i] = '\0';
		return (srclen + dstlen);
	}
}
