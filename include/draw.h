/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:33:26 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/23 05:33:34 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <struct.h>

void	put_pixel(int *addr, const int x, const int y, const int color);
void	safe_put_pixel(int *addr, const int x, const int y, const int color);
void	draw_line(t_data *data, t_vec2i point_a, t_vec2i point_b);
void	rasterization(t_data *mlx);

#endif
