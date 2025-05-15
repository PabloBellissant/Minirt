/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:25:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:04 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Outputs the string ’s’ to the given file 
 * descriptor followed by a newline.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 * @author Bellissant Pablo
 */
void	ft_putendl_fd(char *s, int fd)
{
	char	*temp;

	if (!s)
	{
		ft_putchar_fd('\n', fd);
		return ;
	}
	temp = ft_strjoin(s, "\n");
	ft_putstr_fd(temp, fd);
	free(temp);
}
