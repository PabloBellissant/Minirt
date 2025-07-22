/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:37:41 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/01 01:31:05 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

size_t	get_line_len(char *str);

void	shift_back(char *dest, char *src);

char	*ft_get_line(int fd, char *s_spill, ssize_t read_len, size_t sep_len);

/*
	Function that returns each line of the fd.
*/
char	*get_next_line(int fd)
{
	static char	s_spill[MAX_FD + 1][BUFFER_SIZE + 1];
	char		*line;
	size_t		sep_len;

	sep_len = 0;
	line = NULL;
	if ((fd > MAX_FD) || (fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	if (s_spill[fd][0])
		sep_len = get_line_len(s_spill[fd]);
	if (sep_len)
	{
		line = ft_strndup_gnl(s_spill[fd], sep_len);
		shift_back(s_spill[fd], s_spill[fd] + sep_len);
	}
	else
		line = ft_get_line(fd, s_spill[fd], 0, 0);
	return (line);
}

/*
	Function that returns the position of the next \n or 0.
*/
size_t	get_line_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

/*
	Function that moves and copy from src to dest, meant to be used
	with stack allocated arrays and arrays that do NOT overlap
*/
void	shift_back(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/*
	Function that reads and add to the buffer, until finding a sep or EOF
	Sets any overflow to the leftover static variable.
*/
char	*ft_get_line(int fd, char *s_spill, ssize_t read_len, size_t sep_len)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;

	if (*s_spill)
	{
		line = ft_strndup_gnl(s_spill, 0);
		ft_memset(s_spill, 0, sizeof(s_spill));
	}
	else
		line = ft_calloc(sizeof(char), 1);
	while (1)
	{
		read_len = read(fd, ft_memset(buffer, 0, sizeof(buffer)), BUFFER_SIZE);
		if ((read_len < 0) || ((read_len == 0) && (!*line)))
			return (free(line), ft_memset(s_spill, 0, sizeof(s_spill)), NULL);
		sep_len = get_line_len(buffer);
		if (sep_len)
		{
			shift_back(s_spill, buffer + sep_len);
			buffer[sep_len] = '\0';
		}
		line = ft_strjoin_gnl(line, buffer);
		if (sep_len || !line || (read_len == 0))
			return (line);
	}
}
