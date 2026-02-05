/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:23:53 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 16:30:06 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "render.h"

void	free_bvh_structures(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->bvh.triangle_bvh4)
	{
		free(scene->bvh.triangle_bvh4);
		scene->bvh.triangle_bvh4 = NULL;
		scene->bvh.triangle_bvh4_size = 0;
	}
	if (scene->bvh.sphere_bvh4)
	{
		free(scene->bvh.sphere_bvh4);
		scene->bvh.sphere_bvh4 = NULL;
		scene->bvh.sphere_bvh4_size = 0;
	}
	if (scene->bvh.triangle_bvh8)
	{
		free(scene->bvh.triangle_bvh8);
		scene->bvh.triangle_bvh8 = NULL;
		scene->bvh.triangle_bvh8_size = 0;
	}
	if (scene->bvh.sphere_bvh8)
	{
		free(scene->bvh.sphere_bvh8);
		scene->bvh.sphere_bvh8 = NULL;
		scene->bvh.sphere_bvh8_size = 0;
	}
}
