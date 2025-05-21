/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:27:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/18 00:27:44 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json.h"

static t_json	*init_node(char *json_text);

t_json	*recursive_parse(char *json_text)
{
	t_json	*json;
	char	*next;
	size_t	key_len;

	if (*json_text == '{')
		++json_text;
	json = init_node(json_text);
	if (!json)
		return (NULL);
	key_len = extract_len(json_text);
	if (fill_json_data(json, json_text + key_len + 1) == -1)
	{
		free(json);
		return (NULL);
	}
	next = get_next_data(json_text + key_len);
	if (next)
	{
		json->next = recursive_parse(next + 1);
		if (!json->next)
		{
			free(json);
			return (NULL);
		}
	}
	json->key[key_len] = '\0';
	return (json);
}

static t_json	*init_node(char *json_text)
{
	t_json	*json;

	json = malloc(sizeof(t_json));
	if (!json)
		return (NULL);
	ft_bzero(json, sizeof(t_json));
	json->key = json_text;
	return (json);
}
