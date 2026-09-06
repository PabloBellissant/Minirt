/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_mat_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:35:16 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:14:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_texture(t_opencl *state, t_scene *scene);

void	apply_mat_changes(t_hbranch *hbranch, t_data *data)
{
	(void)hbranch;
	fill_texture(&data->cl, &data->scene);
}

void	apply_to_rgb_int(t_hbranch *hbranch, t_rgb_int *rgb, t_data *data)
{
	*rgb = rgb_ftoi(hbranch->colorpicker.rgb);
	apply_mat_changes(hbranch, data);
}

void	apply_to_rgb(t_hbranch *hbranch, t_rgb *rgb, t_data *data)
{
	*rgb = hbranch->colorpicker.rgb;
	apply_mat_changes(hbranch, data);
}

void	apply_to_tex_col(t_hbranch *hbranch, uint8_t *pixels, t_data *data)
{
	const t_rgb_int	col = rgb_ftoi(hbranch->colorpicker.rgb);

	pixels[0] = col.r;
	pixels[1] = col.g;
	pixels[2] = col.b;
	apply_mat_changes(hbranch, data);
}

void	apply_to_grayscale(t_hbranch *hbranch, uint8_t *pixel, t_data *data)
{
	*pixel = clamp_float_to_byte(hbranch->slider.value);
	apply_mat_changes(hbranch, data);
}
