/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:34:46 by pabellis          #+#    #+#             */
/*   Updated: 2025/03/21 04:42:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#define BUFFER_SIZE 256

static ssize_t	read_buffer_first(char *buffer, t_vector *vec, int fd);
static char		*put_to_buffer(t_vector *vec, char *buffer);
static int		set_size(t_vector *vec);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		i;
	t_vector	vec;

	vector_init(&vec, sizeof(char));
	i = BUFFER_SIZE;
	while (i > 0)
	{
		if (set_size(&vec) == -1)
		{
			free(vec.data);
			return (NULL);
		}
		i = read_buffer_first(buffer, &vec, fd);
		if (i == -1 || vec.num_elements == 0)
		{
			free(vec.data);
			return (NULL);
		}
		if (put_to_buffer(&vec, buffer) != NULL)
			return (vec.data);
	}
	((char *)vec.data)[vec.num_elements] = 0;
	return (vec.data);
}

static int	set_size(t_vector *vec)
{
	if (vec->max_elements - vec->num_elements <= BUFFER_SIZE)
	{
		if (set_vector_size(vec, BUFFER_SIZE + vec->num_elements) == -1)
			return (-1);
	}
	return (0);
}

static char	*put_to_buffer(t_vector *vec, char *buffer)
{
	char	*new_line;
	size_t	size_to_put;

	new_line = ft_memchr(vec->data, '\n', vec->num_elements);
	if (new_line != NULL)
	{
		size_to_put = (char *)(vec->data + vec->num_elements) - new_line - 1;
		ft_memcpy(buffer, new_line + 1, size_to_put);
		buffer[size_to_put] = 0;
		*(new_line + 1) = 0;
		return (vec->data);
	}
	return (NULL);
}

static ssize_t	read_buffer_first(char *buffer, t_vector *vec, int fd)
{
	ssize_t	buffer_len;
	ssize_t	output;

	buffer_len = ft_strlen(buffer);
	if (buffer_len > 0)
	{
		ft_memcpy((char *)vec->data + vec->num_elements, buffer, buffer_len);
		buffer[0] = 0;
		vec->num_elements += buffer_len;
		return (BUFFER_SIZE);
	}
	output = read(fd, vec->data + vec->num_elements, BUFFER_SIZE);
	vec->num_elements += output;
	return (output);
}
