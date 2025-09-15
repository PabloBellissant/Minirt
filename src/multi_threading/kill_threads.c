/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:40:07 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/26 04:40:09 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "threading.h"

void	kill_threads(t_queue *queue, size_t max)
{
	size_t	i;

	pthread_mutex_lock(&queue->stop_mutex);
	i = 0;
	while (i < max)
	{
		pthread_join(queue->threads[i], NULL);
		++i;
	}
	pthread_mutex_unlock(&queue->stop_mutex);
	pthread_mutex_destroy(&queue->stop_mutex);
	pthread_mutex_destroy(&queue->mutex_queue);
}
