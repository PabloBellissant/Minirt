/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:51 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 19:00:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_on_screen(t_ray *rays, int *addr, int pixel)
{
	addr[pixel] = rgb_ftoi(rays[pixel].accumulated_color).rgb;
}

