/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:35:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/18 00:35:42 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json.h"

t_json	*fill_array(char *json_str)
{
	t_json	*json;
	size_t	len;

	json = malloc(sizeof(t_json));
	if (!json)
		return (NULL);
	ft_bzero(json, sizeof(t_json));
	if (*json_str == '[')
		++json_str;
	fill_json_data(json, json_str);
	len = extract_len(json_str);
	if (json_str[len] == ',')
	{
		json->next = fill_array(json_str + len + 1);
		if (!json->next)
		{
			free(json);
			return (NULL);
		}
	}
	return (json);
}
