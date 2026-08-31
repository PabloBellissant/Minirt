/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_med_prim.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:49:11 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 19:37:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_MED_PRIM_H
# define BVH_MED_PRIM_H

typedef enum e_axis			t_axis;
typedef union u_bvh_bounds	t_bvh_bounds;
typedef struct s_bvh_header	t_bvh_header;
typedef struct s_bvh_aabb	t_bvh_aabb;

void	sort_prim_by_axis(t_object *objects, size_t size, t_axis axis_idx);

#endif//BVH_MED_PRIM_H
