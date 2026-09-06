/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pca_mean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:40:07 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 12:22:39 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "matrices.h"
#include "bvh.h"

static inline void	pca_sum_point(t_vec3 *sum, size_t *n, t_vec3 p)
{
	*sum = vec3_add(*sum, p);
	(*n)++;
}

static inline void	pca_sum_triangle(t_vec3 *sum, size_t *n,
						const t_triangle tri)
{
	pca_sum_point(sum, n, tri.p0.pos);
	pca_sum_point(sum, n, tri.p1.pos);
	pca_sum_point(sum, n, tri.p2.pos);
}

static inline void	pca_sum_object_mean(t_vec3 *sum, size_t *n,
						const t_object o)
{
	if (o.type == TRIANGLE)
		pca_sum_triangle(sum, n, o.triangle);
	else
		pca_sum_point(sum, n, o.centroid);
}

t_vec3	pca_mean_objects(t_vector objs, size_t *out_n)
{
	t_object	*o;
	t_vec3		sum;
	size_t		n;
	size_t		i;

	sum = vec3_zero();
	n = 0;
	o = (t_object *)objs.data;
	i = 0;
	while (i < objs.num_elements)
	{
		pca_sum_object_mean(&sum, &n, o[i]);
		i++;
	}
	if (out_n)
		*out_n = n;
	if (n == 0)
		return (vec3_zero());
	return (vec3_div_scalar(sum, (float)n));
}
