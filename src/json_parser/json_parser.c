/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:41:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 00:42:14 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json.h"

t_json	*json_parser(char *json_text)
{
	t_json	*json;
	char	*next;
	size_t	key_len;

	json = malloc(sizeof(t_json));
	if (!json)
		return (NULL);
	ft_bzero(json, sizeof(t_json));
	if (*json_text == '{')
		++json_text;
	json->key = json_text;
	key_len = extract_len(json_text);
	fill_json_data(json, json_text + key_len + 1);
	next = get_next_data(json_text + key_len);
	if (next)
	{
		json->next = json_parser(next + 1);
		if (!json->next)
		{
			free(json);
			return (NULL);
		}
	}
	json->key[key_len] = '\0';
	return (json);
}
