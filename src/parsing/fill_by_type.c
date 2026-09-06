/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_by_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:25:34 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/16 09:57:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "render.h"
#include "parsing.h"

int	create_global_bvh(t_bvh_header **bvh_header, t_vector primitives);

int	fill_by_type(t_opencl *state, t_scene *scene)
{
	if (create_global_bvh(&scene->bvh.world_bvh, scene->objects) != 0)
		return (1);
	if (fill_gpu_data(state, scene) == -1)
		return (-1);
	return (0);
}
