/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:03:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 16:42:06 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"
#include "struct.h"
#include "bvh.h"

#define BUFFER_SIZE 2560000

t_vector	read_file(char *file_name);
char		*get_binary(t_vector *file);
t_vec3		*parse_vec3f_array(unsigned char *data, int nbr);
size_t		get_json_len(t_vector *file);

int parse_map(char *file_name, t_scene *scene)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (!fd)
		return (-1);
	if (rt_parser(fd, scene) == -1)
		return (-1);
	if (create_bvh(scene) == -1)
		return (-1);
	return (0);
}

size_t	get_json_len(t_vector *file)
{
	char	*data;
	size_t	i;
	int		brace_count;
	bool	started;

	data = file->data;
	brace_count = 0;
	started = false;
	i = 0;
	while (i < file->num_elements && (brace_count != 0 || !started))
	{
		if (data[i] == '{')
		{
			started = true;
			++brace_count;
		}
		else if (data[i] == '}')
			--brace_count;
		++i;
	}
	return (i);
}

char	*get_binary(t_vector *file)
{
	char	*data;
	size_t	json_end;

	json_end = get_json_len(file);
	while (json_end % 4 != 0)
		++json_end;
	data = file->data + json_end + 4 + 4;
	return (data);
}

t_vector	read_file(char *file_name)
{
	int			fd;
	t_vector	vec;
	ssize_t		i;

	vector_init(&vec, sizeof(char));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (vec);
	i = BUFFER_SIZE;
	while (i == BUFFER_SIZE)
	{
		if (set_vector_size(&vec, vec.num_elements + BUFFER_SIZE) == -1)
		{
			free_vector(&vec);
			close(fd);
			return (vec);
		}
		i = read(fd, vec.data + vec.num_elements, BUFFER_SIZE);
		vec.num_elements += i;
	}
	if (close(fd) == -1 || i == -1)
		free_vector(&vec);
	return (vec);
}
