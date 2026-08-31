/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_bounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 07:14:59 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:31:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

void	sah_object_bounds(const t_bvh_shape bvh_shape,
		const t_bvh_bounds parent_bounds, const t_object *obj,
		t_bvh_bounds *out)
{
	t_bvh_build_pack	pack;
	t_vector			view;

	(void)parent_bounds;
	ft_bzero(out, sizeof(*out));
	ft_bzero(&pack, sizeof(pack));
	view.element_size = sizeof(t_object);
	view.num_elements = 1;
	view.max_elements = 1;
	view.data = (t_object *)obj;
	pack.primitives = view;
	evaluate_bounds(bvh_shape, &pack);
	*out = pack.bounds;
}
