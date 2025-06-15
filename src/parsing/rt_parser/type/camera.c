/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 08:02:03 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/15 08:02:04 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

int	camera(char *line, int actual_line, t_scene *scene)
{
	line = ft_strtok(line, " ");
	line = ft_strtok(NULL, " ");
	if (line == NULL)
	{
		bad_camera(actual_line);
		return (-1);
	}
}
