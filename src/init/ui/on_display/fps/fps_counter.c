/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:50:36 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 20:30:09 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>

void	fps_counter(int frame)
{
	static int				frames = 0;
	static long				last_time = 0;
	struct timeval			tv;
	long					current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (last_time == 0)
		last_time = current_time;
	frames++;
	if (current_time - last_time >= 1000)
	{
		printf("FPS: %d, samples : %d\n", frames, frame);
		frames = 0;
		last_time = current_time;
	}
}
