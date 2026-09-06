/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:39:01 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 20:12:39 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RELOAD_UTILS_H
# define RELOAD_UTILS_H

void	apply_mat_changes(t_hbranch *hbranch, t_data *data);
void	apply_to_rgb_int(t_hbranch *hbranch, t_rgb_int *rgb, t_data *data);
void	apply_to_rgb(t_hbranch *hbranch, t_rgb *rgb, t_data *data);
void	apply_to_tex_col(t_hbranch *hbranch, uint8_t *pixels, t_data *data);
void	apply_to_grayscale(t_hbranch *hbranch, uint8_t *pixel, t_data *data);
void	reload_gpu(t_hbranch *hbranch, t_data *data);

#endif//RELOAD_UTILS_H
