/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_brackets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:13:25 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:13:27 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

char	*get_end_brackets(char *json_text)
{
	char	bracket_type;
	char	opposite_bracket;
	int		bracket_depth;

	bracket_type = *json_text;
	opposite_bracket = ']';
	if (bracket_type == '{')
		opposite_bracket = '}';
	bracket_depth = 1;
	++json_text;
	while (bracket_depth != 0)
	{
		if (*json_text == bracket_type)
			++bracket_depth;
		else if (*json_text == opposite_bracket)
			--bracket_depth;
		++json_text;
	}
	return (json_text - 1);
}
