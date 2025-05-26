/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:25:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/23 05:25:26 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"

inline void	put_pixel(int *addr, const int x, const int y, const int color)
{
	addr[y * SCREEN_WIDTH + x] = color;
}
