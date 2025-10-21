/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_triangle_outline.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:02:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/15 23:24:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rasterize_triangle_outline(t_img_data *img, t_triangle *triangle,
	int color, t_camera *camera)
{
	t_3d_line	line;

	line = (t_3d_line){triangle->p0.pos, triangle->p1.pos};
	rasterize_3d_line(img, &line, color, camera);
	line = (t_3d_line){triangle->p1.pos, triangle->p2.pos};
	rasterize_3d_line(img, &line, color, camera);
	line = (t_3d_line){triangle->p2.pos, triangle->p0.pos};
	rasterize_3d_line(img, &line, color, camera);
}
