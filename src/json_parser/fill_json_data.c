/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_json_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:18:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:18:26 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"

int	fill_json_data(t_json *json, char *json_text)
{
	json->type = get_type(json_text);
	if (json->type == JSON_BOOL)
	{
		json->boolean = false;
		if (*json_text == 't')
			json->boolean = true;
	}
	else if (json->type == JSON_NUMBER)
		json->number = ft_atod(json_text);
	else if (json->type == JSON_ARRAY)
		json->child = NULL;//fill_array(json_text);
	else if (json->type == JSON_OBJECT)
	{
		json->child = json_parser(json_text);
		if (json->child == NULL)
			return (-1);
	}
	else if (json->type == JSON_STRING)
		json->string = json_text;
	return (0);
}
