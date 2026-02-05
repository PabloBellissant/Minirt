/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:00:17 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 15:04:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"
#include "object.h"

t_vec3	get_bin_centroid(t_object *objects, int obj_idx)
{
	return (get_center(&objects[obj_idx]));
}

void	eval_min_max(t_vec3 *out[MM], t_vec3 a[MM], t_vec3 b[MM])
{
	out[MMIN]->x = fminf(a[MMIN].x, b[MMIN].x);
	out[MMIN]->y = fminf(a[MMIN].y, b[MMIN].y);
	out[MMIN]->z = fminf(a[MMIN].z, b[MMIN].z);
	out[MMAX]->x = fmaxf(a[MMAX].x, b[MMAX].x);
	out[MMAX]->y = fmaxf(a[MMAX].y, b[MMAX].y);
	out[MMAX]->z = fmaxf(a[MMAX].z, b[MMAX].z);
}

void	get_sah_centroid_bounds(t_vector *index_vec, t_object *objects,
											t_vec3 *min, t_vec3 *max)
{
	t_vec2i	*indices;
	t_vec3	c;
	size_t	i;

	*min = vec3(SM, SM, SM);
	*max = vec3(-SM, -SM, -SM);
	indices = (t_vec2i *)index_vec->data;
	i = 0;
	while (i < index_vec->num_elements)
	{
		c = get_bin_centroid(objects, indices[i].x);
		eval_min_max((t_vec3 *[MM]){min, max}, (t_vec3[MM]){*min, *max}, (t_vec3[MM]){c, c});
		i++;
	}
}
