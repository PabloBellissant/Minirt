/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_only_visible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:59:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/11 00:59:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "minirt.h"

void	draw_only_visible(t_img_data *img, t_vec3 *v1, t_vec3 *v2, int color, t_camera *camera)
{
	t_vec2i	proj1;
	t_vec2i	proj2;

	proj1 = project_point(v1, camera);
	proj2 = project_point(v2, camera);
	if (proj1.x != -1 && proj2.x != -1)
		ft_mlx_line_put(img, proj1, proj2, color);
}
