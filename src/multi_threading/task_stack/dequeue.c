/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:24:11 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/26 04:24:13 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "threading.h"

int	dequeue(t_task *task, t_queue *queue)
{
	pthread_mutex_lock(&queue->mutex_queue);
	if (queue->len == 0)
	{
		pthread_mutex_unlock(&queue->mutex_queue);
		return (-1);
	}
	*task = queue->queue[queue->start];
	++queue->start;
	if (queue->start >= TASK_MAX)
		queue->start = 0;
	--queue->len;
	pthread_mutex_unlock(&queue->mutex_queue);
	return (0);
}
