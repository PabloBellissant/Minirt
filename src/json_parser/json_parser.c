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

#include "libft.h"
#include "json.h"

static void	remove_whitespace(char *json_text);
static bool	is_whitespace(char c);
static void	fix_json(t_json *json);

t_json	*json_parser(char *json_text)
{
	size_t	i;
	t_json	*json;

	remove_whitespace(json_text);
	i = 0;
	while (json_text[i] != '{' && json_text[i] != '[')
		++i;
	json = recursive_parse(json_text + i);
	if (!json)
		return (NULL);
	fix_json(json);
	return (json);
}

static void	fix_json(t_json *json)
{
	if (json->next)
		fix_json(json->next);
	if (json->type == JSON_OBJECT || json->type == JSON_ARRAY)
		fix_json(json->child);
	if (json->type == JSON_STRING)
		json->string[extract_len(json->string)] = '\0';
}

static void	remove_whitespace(char *json_text)
{
	while (*json_text)
	{
		if (*json_text == '"')
			json_text = ft_strchr(json_text + 1, '"') + 1;
		if (is_whitespace(*json_text))
			ft_memmove(json_text, json_text + 1, ft_strlen(json_text));
		else
			++json_text;
	}
}

static bool	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == ' '
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (true);
	}
	return (false);
}
