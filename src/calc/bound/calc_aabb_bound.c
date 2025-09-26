/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_aabb_bound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:40:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 00:40:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "render.h"

void	calc_aabb_bound(t_camera *cam, t_bound *bound, t_aabb_bvh *bvh)
{
	t_vec3	vertices[8];
	t_vec2i	proj;
	int		i;

	get_cuboid_vertice(vertices, &bvh->cuboid);
	i = 0;
	while (i < 8)
	{
		proj = project_point(&vertices[i], cam);
		if (apply_bound(&proj, bound) == -1)
			return ;
		++i;
	}
}
