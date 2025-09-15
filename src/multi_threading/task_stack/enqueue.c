/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:20:04 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/26 04:20:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "threading.h"

int	enqueue(t_task *task, t_queue *queue)
{
	int	new_place;

	pthread_mutex_lock(&queue->mutex_queue);
	if (queue->len == TASK_MAX)
	{
		pthread_mutex_unlock(&queue->mutex_queue);
		return (-1);
	}
	new_place = queue->start + queue->len;
	if (new_place >= TASK_MAX)
		new_place -= TASK_MAX;
	queue->queue[new_place] = *task;
	++queue->len;
	pthread_mutex_unlock(&queue->mutex_queue);
	return (0);
}
