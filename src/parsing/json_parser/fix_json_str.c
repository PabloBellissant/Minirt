/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_json_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:20:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/29 01:20:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

static void	remove_quotes(char **str);

void	fix_json_str(t_json *json)
{
	if (json->next)
		fix_json_str(json->next);
	if (json->type == JSON_OBJECT || json->type == JSON_ARRAY)
		fix_json_str(json->child);
	if (json->type == JSON_STRING)
		remove_quotes(&json->string);
	if (!json->key)
		return ;
	remove_quotes(&json->key);
}

static void	remove_quotes(char **str)
{
	size_t	str_len;

	str_len = extract_len(*str) - 1;
	if (((*str)[0] == '"' && (*str)[str_len] == '"')
		|| ((*str)[0] == '\'' && (*str)[str_len] == '\''))
	{
		(*str)[str_len] = '\0';
		++(*str);
	}
	else
		(*str)[str_len] = '\0';
}
