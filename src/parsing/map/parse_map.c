/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:03:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/21 01:04:01 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"
#include "struct.h"

#define BUFFER_SIZE 1024

char	*read_file(char *file_name);

int parse_map(char *file_name, t_scene *scene)
{
	char	*file;

	file = read_file(file_name);
	if (!file)
		return (-1);
	dprintf(2, "%s\n", file + 20);
	(void) scene;
	return (0);
}

char	*read_file(char *file_name)
{
	int			fd;
	t_vector	vec;
	ssize_t		i;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	vector_init(&vec, sizeof(char));
	i = BUFFER_SIZE;
	while (i == BUFFER_SIZE)
	{
		if (set_vector_size(&vec, vec.num_elements + BUFFER_SIZE) == -1)
		{
			free_vector(&vec);
			close(fd);
			return (NULL);
		}
		i = read(fd, vec.data + vec.num_elements, BUFFER_SIZE);
	}
	close(fd);
	if (i == -1)
		free_vector(&vec);
	return (vec.data);
}
