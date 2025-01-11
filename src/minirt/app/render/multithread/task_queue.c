/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:14:33 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:50:21 by damien           ###   ########.fr       */
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
	int		count;

	pthread_mutex_lock(queue_mutex);
	if (*nb_tasks_remain == 0 || !*queue)
	{
		pthread_mutex_unlock(queue_mutex);
		return NULL;
	}
	head = *queue;
	count = 0;
	while (*queue && count < BATCH_SIZE)
	{
		*queue = (*queue)->next;
		count++;
		(*nb_tasks_remain)--;
	}
	if (!*queue)
		*nb_tasks_remain = 0;
	if (*nb_tasks_remain > 0)
		sem_post(jobs_sem);
	tmp = head;
	while (tmp->next && count > 1)
	{
		tmp = tmp->next;
		count--;
	}
	tmp->next = NULL;
	pthread_mutex_unlock(queue_mutex);
	return head;
}

void	reset_task_queue(t_render *render)
{
	sem_init(&render->sync.jobs_sem, 0, 0);
	pthread_mutex_lock(&render->sync.queue_mut);
	render->sync.nb_tasks_remain = 0;
	del_queue(&render->queue);
	pthread_mutex_unlock(&render->sync.queue_mut);
}
