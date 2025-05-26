/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:35:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 22:35:37 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "threading.h"

void	*routine(void *args)
{
	t_queue *queue;
	t_task	task;

	queue = (t_queue *)args;
	while (queue->stop_mutex.__data.__lock == 0)
	{
		if (dequeue(&task, queue) == 0)
			task.f(task.data);
		else
			usleep(1000);
	}
	return (NULL);
}

