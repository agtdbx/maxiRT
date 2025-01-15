/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:14:33 by damien            #+#    #+#             */
/*   Updated: 2025/01/12 19:30:25 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/render/multithread/multithread.h"

#include <stdlib.h>

#define FRONT_CANVAS 0
#define BACK_CANVAS 1
#define BATCH_SIZE 64

t_task	*init_tasks_queue()
{
	t_task	*lst;

	lst = malloc(sizeof(t_task));
	if (lst == NULL)
		return NULL;
	lst->next = NULL;
	return lst;
}

void	del_queue(t_task **queue)
{
	t_task	*tmp;

	while (*queue != NULL)
	{
		tmp = *queue;
		*queue = (*queue)->next;
		free(tmp);
	}
	*queue = NULL;
}

void	push_task(t_task **queue, t_task *new_task, int *nb_task_remain)
{
	if (*queue == NULL)
	{
		*queue = new_task;
		new_task->next = NULL;
		(*nb_task_remain)++;
		return ;
	}
	new_task->next = *queue;
	*queue = new_task;
	(*nb_task_remain)++;
}

t_task	*pop_task_lst(
	t_task **queue,
	pthread_mutex_t *queue_mutex,
	int *nb_tasks_remain,
	sem_t *jobs_sem)
{
	t_task	*head;
	t_task	*tmp;
	t_task	*prev;
	int		i;

	pthread_mutex_lock(queue_mutex);
	if (!*queue)
	{
		*nb_tasks_remain = 0;
		pthread_mutex_unlock(queue_mutex);
		return NULL;
	}
	head = *queue;
	tmp = *queue;
	for (i = 0; i < BATCH_SIZE; i++)
	{
		if (tmp == NULL)
			break;
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
	{
		prev->next = NULL;
		*queue = tmp;
		*nb_tasks_remain -= i;
		if (*nb_tasks_remain > 0)
			sem_post(jobs_sem);
	}
	else
	{
		*queue = NULL;
		*nb_tasks_remain = 0;
	}
	pthread_mutex_unlock(queue_mutex);
	return head;
}

void	reset_task_queue(t_render *render)
{
	render->sync.reset_render = true;
	pthread_mutex_lock(&render->sync.queue_mut);
	del_queue(&render->queue);
	pthread_mutex_unlock(&render->sync.queue_mut);
}
