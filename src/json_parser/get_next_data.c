/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:14:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:14:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"

char	*get_next_data(char *json_text)
{
	char	*old;

	old = json_text;
	while (*json_text
		&& *json_text != ',' && *json_text != '}' && *json_text != ']')
	{
		if (*json_text == '"')
			json_text = ft_memchr(json_text + 1, '"', 10000);
		else if (*json_text == '{' || *json_text == '[')
			json_text = get_end_brackets(json_text);
		++json_text;
	}
	if (*json_text == '}' || *json_text == ']')
		return (NULL);
	return (json_text);
}
