/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:08:31 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 22:08:34 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "libft.h"
#include "threading.h"

int	init_threads(t_queue *queue)
{
	size_t	i;

	if (pthread_mutex_init(&queue->mutex_queue, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&queue->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&queue->mutex_queue);
		return (-1);
	}
	i = 0;
	while (i < THREADS_COUNT)
	{
		if (pthread_create(&queue->threads[i], NULL, routine, queue) != 0)
		{
			kill_threads(queue, i);
			return (-1);
		}
		++i;
	}
	return (0);
}
