/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cohen_sutherland_clip.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:36:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/17 17:36:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	compute_out(t_img_data *img, t_vec2i pos);

bool	is_out_screen(t_img_data *img, t_vec2i *a, t_vec2i *b)
{
	int		out0;
	int		out1;

	out0 = compute_out(img, *a);
	out1 = compute_out(img, *b);
	if (out0 & out1)
		return (false);
	return (true);
}

static int	compute_out(t_img_data *img, t_vec2i pos)
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
