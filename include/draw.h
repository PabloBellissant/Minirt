/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:33:26 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 18:54:00 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <struct.h>

void	put_pixel(int *addr, const int x, const int y, const int color);
void	safe_put_pixel(int *addr, const int x, const int y, const int color);

#endif
