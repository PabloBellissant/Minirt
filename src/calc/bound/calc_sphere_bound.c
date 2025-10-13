/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sphere_bound.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:41:06 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 00:41:09 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

#define VERTICES_COUNT 1008

static void	get_sphere_vertice(t_vec3 vertices[VERTICES_COUNT],
				t_sphere_bvh *bvh);

void	calc_sphere_bound(t_camera *cam, t_bound *bound, t_sphere_bvh *bvh)
{
	t_vec3	vertices[VERTICES_COUNT];
	t_vec2i	proj;
	int		i;

	get_sphere_vertice(vertices, bvh);
	i = 0;
	while (i < VERTICES_COUNT)
	{
		proj = project_point(&vertices[i], cam);
		if (apply_bound(&proj, bound) == -1)
			return ;
		++i;
	}
}

static void	get_sphere_vertice(t_vec3 vertices[VERTICES_COUNT],
				t_sphere_bvh *bvh)
{
	float	val;
	float	i;
	int		j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		val = 0.0f;
		while (val <= 2.0f * M_PIf)
		{
			vertices[j].x = bvh->pos.x + (bvh->size * 1.02f)
				* sinf(i * M_PIf / 16) * cosf(val);
			vertices[j].y = bvh->pos.y + (bvh->size * 1.02f)
				* cosf(i * M_PIf / 16);
			vertices[j].z = bvh->pos.z + (bvh->size * 1.02f)
				* sinf(i * M_PIf / 16) * sinf(val);
			++j;
			val += 0.1f;
		}
		++i;
	}
}
