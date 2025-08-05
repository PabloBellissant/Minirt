/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:25:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:47 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

inline void	put_pixel(int *addr, const int x, const int y, const int color)
{
	addr[y * WIDTH + x] = color;
}

inline void	safe_put_pixel(int *addr, const int x, const int y, const int color)
{
	if ((x < 0) || (x > WIDTH))
		return ;
	if ((y < 0) || (y > HEIGHT))
		return ;
	put_pixel(addr, x, y, color);
}
