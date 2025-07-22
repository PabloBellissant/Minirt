/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 06:52:51 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 06:55:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;

	dup = ft_calloc(sizeof(char), (n + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, str, n);
	return (dup);
}
