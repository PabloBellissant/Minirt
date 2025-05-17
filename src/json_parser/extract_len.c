/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:17:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:17:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"

size_t	extract_len(char *json_text)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (*json_text == '"')
	{
		temp = ft_strchr(json_text + 1, '"') + 1;
		if (!temp)
			return (0);
		i = temp - json_text;
	}
	while (json_text[i] && json_text[i] != ':'
		&& json_text[i] != ',' && json_text[i] != '}' && json_text[i] != ']')
	{
		++i;
	}
	return (i);
}
