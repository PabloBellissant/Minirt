/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:16:42 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/10 04:57:33 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "parsing.h"
# include "object.h"
# include "vectors.h"
# include "libft.h"
# include <float.h>
# include "bvh_splitting.h"
# include "bvh_shape.h"
# include "bvh_build_utils.h"
# include "bvh_utils.h"

# define BVH_ARITY 2

typedef struct s_scene		t_scene;
typedef struct s_object		t_object;

typedef struct s_bvh_header
{
	t_vector	nodes;
	int			max_depth;
	t_bvh_shape	shape;
	t_bvh_split	splitting_algo;
	size_t		build_time;
}				t_bvh_header;

typedef struct s_bvh_node
{
	union
	{
		int			children[BVH_ARITY];
		struct
		{
			int		_pad[BVH_ARITY - 1];
			int		object_id;
			int		type;
		};
	};
	int				skip;
	t_bvh_bounds	bounds;
}					t_bvh_node;

typedef struct s_bvh_engine
{
	t_bvh_header	*world_best_bvh;
	t_bvh_header	*world_bvh;
	cl_mem			bvh_gpu;
}					t_bvh_engine;

int		create_bvh(t_bvh_header *bvh_header, t_bvh_shape shape,
			t_bvh_split splitting_algo, t_vector primitives);

void	free_bvh(t_bvh_engine bvh);

void	index_bvh(t_bvh_header bvh_header);

#endif//BVH_H
