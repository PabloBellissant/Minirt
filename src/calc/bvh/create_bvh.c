/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:56:15 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 03:45:29 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <sys/time.h>

ssize_t	bvh_subdivide(t_bvh_header *bvh_header, t_vector primitives,
			t_bvh_bounds cur_bounds);

int	free_bvh_build_pack(t_bvh_build_pack childs[BVH_LR])
{
	free_vector(&childs[BVH_L].primitives);
	free_vector(&childs[BVH_R].primitives);
	return (-1);
}

static inline int	bvh_generator(t_bvh_header *bvh_header, t_vector primitives)
{
	t_bvh_build_pack	root;
	ssize_t				ret;

	ft_bzero(&root, sizeof(t_bvh_build_pack));
	root.primitives = primitives;
	if (primitives.num_elements == 0)
	{
		bvh_header->max_depth = 0;
		return (0);
	}
	evaluate_bounds(bvh_header->shape, &root);
	ret = bvh_subdivide(bvh_header, primitives, root.bounds);
	if (ret < 0)
		return (-1);
	bvh_header->max_depth = ret;
	return (0);
}

/*
	Function to compute bvh construction time
*/
static inline int	bvh_wrapper(t_bvh_header *bvh_header, t_vector primitives)
{
	struct timeval	start;
	struct timeval	stop;
	ssize_t			ret;

	ret = gettimeofday(&start, NULL);
	if (ret < 0)
		return (-1);
	ret = bvh_generator(bvh_header, primitives);
	if (ret < 0)
		return (-1);
	ret = gettimeofday(&stop, NULL);
	if (ret < 0)
		return (-1);
	bvh_header->build_time = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	return (0);
}

/*
	need to pass vector of object (triangles for local BVH meshes)
*/
int	create_bvh(t_bvh_header *bvh_header, t_bvh_shape shape,
		t_bvh_split splitting_algo, t_vector primitives)
{
	bvh_header->shape = shape;
	bvh_header->splitting_algo = splitting_algo;
	vector_init(&bvh_header->nodes, sizeof(t_bvh_node));
	return (bvh_wrapper(bvh_header, primitives));
}
