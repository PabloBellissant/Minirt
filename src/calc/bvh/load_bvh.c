/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:53:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 23:53:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bvh.h"

int	load_bvh(int mode, t_scene *scene)
{
	if (scene->bvh.bvh_pointer != NULL)
		free(scene->bvh.bvh_pointer);
	if (mode == 0)
	{
		if (create_sphere_bvh(scene) == -1)
			return (-1);
	}
	else if (mode == 1)
	{
		if (create_aabb_bvh(scene) == -1)
			return (-1);
	}
	return (0);
}
