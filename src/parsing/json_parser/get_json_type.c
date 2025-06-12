/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:16:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:16:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"

t_json_type	get_json_type(char *json_text)
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
