/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 03:29:33 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/09 03:29:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (n == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s1_len || n > s2_len)
		n = fminf(s1_len, s2_len);
	i = 0;
	while (i < n - 1 && (s1[s1_len - i - 1] == s2[s2_len - i - 1]))
		++i;
	return (s1[s1_len - i - 1] - s2[s2_len - i - 1]);
}
