/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:05:30 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/16 09:59:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb_int	float_to_rainbow(float f);

static inline t_rgb_int	depth_to_rgb_int(const int depth, const int total_depth)
{
	float	t;

	t = (float)(depth) / (float)total_depth;
	return (float_to_rainbow(fmodf(t, 1.0f)));
}

static inline void	rasterize_shape(t_data *data,
		t_bvh_header *bvh_header, t_bvh_node node, int depth)
{
	const t_rgb_int	color = depth_to_rgb_int(depth
			+ data->params.color_offset, bvh_header->max_depth);

	if (bvh_header->shape == BVH_AABB)
		rasterize_cuboid(&node.bounds.aabb.cuboid, &data->mlx->img,
			&data->scene.camera, color);
	else if (bvh_header->shape == BVH_SPHERE)
		rasterize_sphere_outline((t_sphere *)&node.bounds.sphere,
			&data->mlx->img, &data->scene.camera, color);
	else if (bvh_header->shape == BVH_OBB)
		rasterize_obb(&node.bounds.obb, &data->mlx->img,
			&data->scene.camera, color);
}

static inline void	rasterize_bvh(t_data *data, t_bvh_header *bvh_header,
						t_bvh_node node, int depth)
{
	size_t		i;

	i = 0;
	if ((data->params.bvh_depth > depth)
		|| (data->params.bvh_depth == -1))
	{
		while ((i < BVH_ARITY) && (node.children[i] > 0))
		{
			rasterize_bvh(data, bvh_header,
				*(t_bvh_node *)get_vector_value(&bvh_header->nodes,
					node.children[i]), depth + 1);
			i++;
		}
	}
	if ((data->params.bvh_depth == depth)
		|| (data->params.bvh_depth == -1))
		rasterize_shape(data, bvh_header, node, depth);
}

void	debug_rasterize_bvh(t_data *data)
{
	if (data->params.bvh_debug && data->scene.bvh.world_bvh)
		rasterize_bvh(data, data->scene.bvh.world_bvh,
			*(t_bvh_node*)get_vector_value(&data->scene.bvh.world_bvh->nodes,
				0), 0);
}
