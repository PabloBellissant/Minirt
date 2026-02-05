/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_out_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:36:13 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/19 19:31:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	compute_out(t_img_data *img, t_vec2i pos)
{
	int	code;

	code = 0b0000;
	if (pos.x < 0)
		code |= 0b0001;
	else if (pos.x >= img->width)
		code |= 0b0010;
	if (pos.y < 0)
		code |= 0b0100;
	else if (pos.y >= img->height)
		code |= 0b1000;
	return (code);
}

bool	is_out_screen(t_img_data *img, t_vec2i *a, t_vec2i *b)
{
	return (!(compute_out(img, *a) & compute_out(img, *b)));
}
