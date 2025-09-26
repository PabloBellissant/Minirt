/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bvh_bound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:40:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 00:40:21 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_aabb_bound(t_camera *cam, t_bound *bound, t_aabb_bvh *bvh);
void	calc_sphere_bound(t_camera *cam, t_bound *bound, t_sphere_bvh *bvh);

void	calc_bvh_bound(t_camera *cam, t_bound *bound, t_bvh_main *bvh, int mode)
{
	bvh->bound.top = HEIGHT;
	bvh->bound.down = 0;
	bvh->bound.left = WIDTH;
	bvh->bound.right = 0;
	if (mode == 0)
		calc_sphere_bound(cam, bound, bvh->sphere_bvh);
	if (mode == 1)
		calc_aabb_bound(cam, bound, bvh->aabb_bvh);
}
