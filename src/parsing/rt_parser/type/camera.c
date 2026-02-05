/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:29:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 09:37:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "rt_xcerrcal.h"
#include "vec3_scalar.h"

#define CAMERA_FORMAT " *C  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1]  *%d[180]\n"

int	camera(const char *line, int line_num, t_scene *scene)
{
	t_camera	*camera;
	t_vec3		*pos;
	t_vec3		*rot;

	camera = &scene->camera;
	pos = &camera->pos;
	rot = &camera->rot;
	if (ft_scan(line_num, CAMERA_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&rot->x, &rot->y, &rot->z, &camera->fov) == -1)
	{
		return (error(pack_err(RT_ID, RT_E_CAMERA), FL, LN, FC));
	}
	*rot = vec3_scale(*rot, M_PI);
	camera->lens_radius = 0.001f;
	camera->focus_dist = 1;
	return (0);
}
