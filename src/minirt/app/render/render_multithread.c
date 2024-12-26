/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_multithread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:39:43 by damien            #+#    #+#             */
/*   Updated: 2024/12/26 16:05:24 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/drawings/drawings.h"

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

long	get_nb_threads()
{
	static long	nb_threads = 0;

	if (nb_threads == 0)
		nb_threads = sysconf(_SC_NPROCESSORS_ONLN);

	return (nb_threads);
}

void	join_all_threads(t_worker *workers)
{
	int		i;
	long	nb_threads;

	nb_threads = get_nb_threads();
	for (i = 0; i < nb_threads - 1; i++)
		pthread_join(workers[i].thid, NULL);
}


t_task	*init_tasks_queue()
{
	t_task	*lst;

	lst = malloc(sizeof(t_task));
	if (lst == NULL)
		return NULL;
	lst->next = NULL;
	return lst;
}

void	del_mut_cond_sem(t_sync *sync)
{
	pthread_mutex_destroy(&sync->queue_mut);
	pthread_mutex_destroy(&sync->canvas_mut[FRONT_CANVAS]);
	pthread_mutex_destroy(&sync->canvas_mut[BACK_CANVAS]);
	pthread_mutex_destroy(&sync->active_threads_mut);
	pthread_cond_destroy(&sync->finish_jobs_cond);
	sem_destroy(&sync->jobs_sem);
}

void	task_cast_ray(t_worker *worker, t_task *task)
{
	mlx_image_t		*img;
	pthread_mutex_t	*img_mutex;

	if (task->back_canvas == 1)
	{
		img = worker->render->canvas->back;
		img_mutex = &worker->render->sync.canvas_mut[BACK_CANVAS];
	}
	else
	{
		img = worker->render->canvas->front;
		img_mutex = &worker->render->sync.canvas_mut[FRONT_CANVAS];
	}

	img_draw_square(
		img_mutex,
		img,
		task->pixels,
		task->ppr,
		render_ray_from_camera(
			worker->render->scene,
			&task->ray,
			worker->render->menu->is_visible
		)
	);
	worker->render->sync.pixel_rendered += task->ppr;
}

void	task_compute_const(t_task *task)
{
	if (task->object->type == OBJ_SPHERE)
		sphere_compute_constants(
			&task->object->value.as_sphere,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_PLANE)
		plane_compute_constants(
			&task->object->value.as_plane,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_CYLINDER)
		cylinder_compute_constants(
			&task->object->value.as_cylinder,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_CONE)
		cone_compute_constants(
			&task->object->value.as_cone,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_CUBE)
		cube_compute_constants(
			&task->object->value.as_cube,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_TRIANGLE)
		triangle_compute_constants(
			&task->object->value.as_triangle,
			&task->object->bounding_box);
	else if (task->object->type == OBJ_OBJECT_FILE)
		object_file_compute_constants(
			&task->object->value.as_object_file,
			&task->object->bounding_box);
}

void	sem_post_value(sem_t *sem, int value)
{
	int	i;

	for (i = 0; i < value; i++)
		sem_post(sem);
}

void	*render_routine(void *data)
{
	t_worker	*worker;
	t_task		*task;

	worker = (t_worker *)data;
	while (worker->render->sync.keep_alive != 0)
	{
		sem_wait(&worker->render->sync.jobs_sem);
		if (!worker->render->sync.keep_alive)
			break;
		pthread_mutex_lock(&worker->render->sync.active_threads_mut);
		worker->render->sync.nb_active_threads++;
		pthread_mutex_unlock(&worker->render->sync.active_threads_mut);
		task = pop_task(
			&worker->render->queue,
			&worker->render->sync.queue_mut,
			&worker->render->sync.nb_tasks_remain);
		if (task == NULL || !worker->render->sync.keep_alive)
			continue;
		switch (task->type)
		{
			case COMPUTE_CONST:
				task_compute_const(task);
				break ;
			default:
				task_cast_ray(worker, task);
				break ;
		}
		free(task);
		task = NULL;
		pthread_mutex_lock(&worker->render->sync.active_threads_mut);
		worker->render->sync.nb_active_threads--;
		if (worker->render->sync.nb_active_threads == 0)
		{
			if (worker->render->sync.nb_tasks_remain == 0)
				pthread_cond_signal(&worker->render->sync.finish_jobs_cond);
		}
		pthread_mutex_unlock(&worker->render->sync.active_threads_mut);
	}
	return NULL;
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

static void	join_prev_threads(t_worker *workers, int i)
{
	for (; i >= 0; i--)
		pthread_join(workers[i].thid, NULL);
}

static t_error	start_threads(t_render *render)
{
	int				i;
	long			nb_threads;
	pthread_attr_t	attr;

	nb_threads = sysconf(_SC_NPROCESSORS_ONLN);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (i = 0; i < nb_threads - 1; i++)
	{
		if (pthread_create(&render->workers[i].thid, &attr,
				render_routine, &render->workers[i]) != 0)
			join_prev_threads(render->workers, i);
	}
	pthread_attr_destroy(&attr);
	return SUCCESS;
}

static void	fill_threads(t_render *render)
{
	int		i;
	long	nb_threads;

	nb_threads = sysconf(_SC_NPROCESSORS_ONLN);
	for (i = 0; i < nb_threads - 1; i++)
		render->workers[i].render = render;
}

t_error	threads_init(t_app *app)
{
	fill_threads(&app->render);
	return start_threads(&app->render);
}

void	push_task(t_task **queue, t_task *new_task, int *nb_task_remain)
{
	new_task->next = *queue;
	*queue = new_task;
	(*nb_task_remain)++;
}

t_task	*pop_task(t_task **queue, pthread_mutex_t *queue_mutex, int *nb_tasks_remain)
{
	t_task	*head;

	pthread_mutex_lock(queue_mutex);
	head = *queue;
	if (head)
		*queue = (*queue)->next;
	else
	{
		pthread_mutex_unlock(queue_mutex);
		return NULL;
	}
	(*nb_tasks_remain)--;
	pthread_mutex_unlock(queue_mutex);
	return head;
}
