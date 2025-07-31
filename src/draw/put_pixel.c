/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:25:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:33:10 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
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
