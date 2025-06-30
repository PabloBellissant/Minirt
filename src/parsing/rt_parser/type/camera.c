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

#define CAMERA_FORMAT " *C +%f *, *%f *, *%f +%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1] +%d[180]\n"

int	camera(char *line, int line_num, t_scene *scene)
{
	t_camera	*camera;
	t_vec3		*pos;
	t_vec3		*rot;

	camera = &scene->camera;
	pos = &camera->pos;
	rot = &camera->rot;
	ft_scan(line_num, CAMERA_FORMAT, line, &pos->x, &pos->y, &pos->z,
		&rot->x, &rot->y, &rot->z, &camera->fov);
	return (0);
}
