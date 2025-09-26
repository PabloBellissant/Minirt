/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:25:12 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 00:25:15 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_bound(t_bound *bound, t_img_data *img)
{
	t_vec2i	c1;
	t_vec2i	c2;
	t_vec2i	c3;
	t_vec2i	c4;

	c1 = vec2i(bound->left, bound->top);
	c2 = vec2i(bound->right, bound->top);
	c3 = vec2i(bound->left, bound->down);
	c4 = vec2i(bound->right, bound->down);
	ft_mlx_line_put(img, c1, c2, 0xFFFFFF);
	ft_mlx_line_put(img, c1, c3, 0xFFFFFF);
	ft_mlx_line_put(img, c2, c4, 0xFFFFFF);
	ft_mlx_line_put(img, c3, c4, 0xFFFFFF);
}
