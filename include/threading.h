/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:37:04 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 20:37:08 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADING_H
# define THREADING_H

# define THREADS_COUNT 1
# define TASK_MAX 512

# include "struct.h"

typedef struct	s_task
{
	int		(*f)(void *);
	void	*data;
}	t_task;

typedef struct	s_task_data
{
	t_data	*data;
	int		i;
}	t_task_data;

typedef struct	s_queue
{
	t_task			queue[TASK_MAX];
	pthread_t		threads[THREADS_COUNT];
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	mutex_queue;
	int				len;
	int				start;
}	t_queue;

int		init_threads(t_queue *queue);
int		enqueue(t_task *task, t_queue *queue);
int		dequeue(t_task *task, t_queue *queue);
void	*routine(void *args);
void	kill_threads(t_queue *queue, size_t max);

#endif
