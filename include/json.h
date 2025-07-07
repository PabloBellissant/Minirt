/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:13:46 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 19:13:51 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_json	t_json;

typedef enum e_json_type
{
	JSON_NULL,
	JSON_BOOL,
	JSON_NUMBER,
	JSON_ARRAY,
	JSON_OBJECT,
	JSON_STRING
}	t_json_type;

typedef struct s_json
{
	char		*key;
	union
	{
		bool	boolean;
		float	number;
		char	*string;
		t_json	*child;
	};
	t_json		*next;
	t_json_type	type;
}	t_json;

t_json		*json_parser(char *json_text);
t_json		*recursive_parse(char *json_text);
char		*get_end_brackets(char *json_text);
char		*get_next_data(char *json_text);
size_t		extract_len(char *json_text);
t_json_type	get_json_type(char *json_text);
int			fill_json_data(t_json *json, char *json_text);
t_json		*fill_array(char *json_str);
t_json		*get_by_key_name(t_json *node, char *name);
void		fix_json_str(t_json *json);

#endif
