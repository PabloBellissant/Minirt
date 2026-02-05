/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:03:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 04:50:37 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "bvh.h"
#include <fcntl.h>
#include "rt_xcerrcal.h"
#include "render.h"

int	parse_scene(char *file_name, t_scene *scene, t_opencl *state)
{
	int	fd;

	if (ft_strrncmp(file_name, ".rt", 3) != 0)
	{
		register_complex_err_msg(RT_E_MSG_ARGS, file_name);
		return (error(pack_err(RT_ID, RT_E_ARGS), FL, LN, FC));
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (rt_parser(fd, scene) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (fill_by_type(state, scene) == -1)
		return (-1); //free
	return (0);
}

