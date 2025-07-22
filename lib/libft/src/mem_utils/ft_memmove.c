/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:12:58 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:53:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest || src)
	{
		if (dest <= src)
			ft_memcpy(dest, src, n);
		else
		{
			i = 0;
			while (i < n)
			{
				((unsigned char *)dest)[n - i - 1]
					= ((const unsigned char *)src)[n - i - 1];
				i++;
			}
		}
	}
	return (dest);
}
