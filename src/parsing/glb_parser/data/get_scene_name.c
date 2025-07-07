/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 04:59:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/29 04:59:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

char	*get_scene_name(t_json *json)
{
	json = get_by_key_name(json, "scenes");
	if (!json || !json->child || !json->child->child)
		return (NULL);
	json = json->child->child;
	json = get_by_key_name(json, "name");
	if (!json)
		return (NULL);
	return (json->string);
}
