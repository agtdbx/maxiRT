/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multithread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:13:15 by damien            #+#    #+#             */
/*   Updated: 2025/01/14 22:07:53 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/render/multithread/multithread.h"

#include <stdlib.h>

static void	_consume_tasks(t_worker *worker, t_task *task_lst);
static void	_send_signal_if_jobs_finish(t_sync *sync);
static void	_free_tasks(t_task *task);

void	*render_routine(void *data)
{
	t_worker	*worker;
	t_task		*task_lst;

	worker = (t_worker *)data;
	while (worker->render->sync.keep_alive != 0)
	{
		sem_wait(&worker->render->sync.jobs_sem);
		if (!worker->render->sync.keep_alive
			|| worker->render->sync.reset_render)
			continue ;
		pthread_mutex_lock(&worker->render->sync.active_threads_mut);
		worker->render->sync.nb_active_threads++;
		pthread_mutex_unlock(&worker->render->sync.active_threads_mut);
		task_lst = pop_task_lst(
			&worker->render->queue,
			&worker->render->sync.queue_mut,
			&worker->render->sync.nb_tasks_remain,
			&worker->render->sync.jobs_sem);
		if (task_lst == NULL || !worker->render->sync.keep_alive
			|| worker->render->sync.reset_render)
		{
			if (task_lst != NULL)
				_free_tasks(task_lst);
			pthread_mutex_lock(&worker->render->sync.active_threads_mut);
			worker->render->sync.nb_active_threads--;
			pthread_mutex_unlock(&worker->render->sync.active_threads_mut);
			continue ;
		}
		_consume_tasks(worker, task_lst);
		_send_signal_if_jobs_finish(&worker->render->sync);
	}
	return NULL;
}

static void	_free_tasks(t_task *task)
{
	t_task	*tmp;

	while (task)
	{
		tmp = task;
		task = task->next;
		free(tmp);
	}
	task = NULL;
}

static void	_send_signal_if_jobs_finish(t_sync *sync)
{
	pthread_mutex_lock(&sync->active_threads_mut);
	if (--sync->nb_active_threads == 0 &&
			sync->nb_tasks_remain == 0)
		pthread_cond_signal(&sync->finish_jobs_cond);
	pthread_mutex_unlock(&sync->active_threads_mut);
}

static void	_consume_tasks(t_worker *worker, t_task *task_lst)
{
	t_task	*tmp;

	while (task_lst)
	{
		task_cast_ray(worker, task_lst);
		if (worker->render->sync.reset_render)
		{
			_free_tasks(task_lst);
			return ;
		}
		tmp = task_lst;
		task_lst = task_lst->next;
		free(tmp);
	}
}

void	wait_jobs_finish(t_render *render)
{
	pthread_mutex_lock(&render->sync.queue_mut);
	while (render->sync.nb_tasks_remain)
		pthread_cond_wait(&render->sync.finish_jobs_cond, &render->sync.queue_mut);
	pthread_mutex_unlock(&render->sync.queue_mut);
}
