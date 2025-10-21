/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_3d_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:29:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/15 22:59:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "minirt.h"
#include "calc.h"

bool	is_out_screen(t_img_data *img, t_vec2i *a, t_vec2i *b);

void	rasterize_3d_line(t_img_data *img, t_3d_line *line,
	int color, t_camera *camera)
{
	t_vec2i	proj1;
	t_vec2i	proj2;

	proj1 = project_point(&line->pos1, camera);
	proj2 = project_point(&line->pos2, camera);
	if (!is_out_screen(img, &proj1, &proj2))
		return ;
	if (proj1.x == -1 || proj2.x == -1)
		return ;
	ft_mlx_line_put(img, proj1, proj2, color);
}
