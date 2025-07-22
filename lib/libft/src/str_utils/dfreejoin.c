/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfreejoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:09:09 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/19 19:01:04 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function that joins s1 and s2 and free boths
*/
char	*dfreejoin(char *s1, char *s2)
{
	char	*new;

	if (!s2)
		new = ft_strdup(s1);
	if (!s1)
		new = ft_strdup(s2);
	else
		new = ft_strjoin(s1, s2);
	return (free(s1), free(s2), new);
}
