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
#include "struct.h"

static char			*extract_str(char *json_text);
static t_json_type	get_type(char *json_text);
static int			fill_json_data(t_json *json, char *json_text);
static char			*get_next_data(char *json_text);

t_json	*json_parser(char *json_text)
{
	t_json	*json;
	char	*next;

	json = malloc(sizeof(t_json));
	if (!json)
		return (NULL);
	json = ft_bzero(json, sizeof(t_json));
	if (*json_text == '{')
		++json_text;
	json->key = extract_str(json_text);
	json->type = get_type(json_text + ft_strlen(json->key) + 1);
	fill_json_data(json, json_text + ft_strlen(json->key) + 1);
	next = get_next_data(json_text + ft_strlen(json->key) + 1);
	if (*next != ']' && *next != '}')
	{
		json->next = json_parser(next + 1);
		if (!json->next)
		{
			free(json);
			return (NULL);
		}
	}
	return (json);
}

static char	*get_next_data(char *json_text)
{
	while (*json_text && *json_text != ':'
		&& *json_text != ',' && *json_text != '}' && *json_text != ']')
	{
		if (*json_text == '"')
			json_text = ft_strchr(json_text + 1, '"');
		++json_text;
	}
	return (json_text);
}

static int	fill_json_data(t_json *json, char *json_text)
{
	if (json->type == JSON_BOOL)
	{
		json->boolean = false;
		if (*json_text == 't')
			json->boolean = true;
	}
	else if (json->type == JSON_NUMBER)
		json->number = ft_atod(json_text);
	else if (json->type == JSON_ARRAY)
		/*json->child = fill_array*/;
	else if (json->type == JSON_OBJECT)
	{
		json->child = json_parser(json_text);
		if (json->child == NULL)
			return (-1);
	}
	else if (json->type == JSON_STRING)
		json->string = extract_str(json_text);
	return (0);
}

static t_json_type	get_type(char *json_text)
{
	if (ft_strncmp(json_text, "null", 4) == 0)
		return (JSON_NULL);
	if (ft_strncmp(json_text, "true", 4) == 0)
		return (JSON_BOOL);
	if (ft_strncmp(json_text, "false", 5) == 0)
		return (JSON_BOOL);
	if (ft_isdigit(*json_text) || *json_text == '-')
		return (JSON_NUMBER);
	if (*json_text == '[')
		return (JSON_ARRAY);
	if (*json_text == '{')
		return (JSON_OBJECT);
	return (JSON_STRING);
}

static char	*extract_str(char *json_text)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (*json_text == '"')
	{
		temp = ft_strchr(json_text + 1, '"') + 1;
		if (!temp)
			return (NULL);
		i = temp - json_text;
	}
	while (json_text[i] && json_text[i] != ':'
		&& json_text[i] != ',' && json_text[i] != '}' && json_text[i] != ']')
	{
		++i;
	}
	json_text[i] = '\0';
	return (json_text);
}
