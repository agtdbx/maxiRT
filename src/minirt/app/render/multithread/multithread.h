/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:02:20 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:56:37 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREAD_H
# define MULTITHREAD_H

# include "minirt/app/menu/menu.h"
# include "minirt/app/scene/scene.h"
# include "minirt/app/canvas/canvas.h"

# include <semaphore.h>
# include <pthread.h>
# include <stdint.h>

typedef struct s_task
{
	t_object		*object;
	int				back_canvas;
	int32_t			ppr;
	t_ray			ray;
	int32_t			pixels[2];
	struct s_task	*next;
}	t_task;


typedef struct s_worker
{
	pthread_t		thid;
	struct s_render	*render;
}	t_worker;


typedef struct s_sync
{
	pthread_rwlock_t	scene_mut;
	pthread_mutex_t		canvas_mut[2];
	// keep track of active threads
	pthread_mutex_t		active_threads_mut;
	// use to check and add job in queue
	pthread_mutex_t		queue_mut;
	pthread_cond_t		finish_jobs_cond;
	// increment/decrement each time a task is added/removed
	sem_t				jobs_sem;
	int					nb_active_threads;
	int					nb_tasks_remain;
	int					pixel_rendered;
	volatile int		keep_alive;
}	t_sync;

typedef struct s_render
{
	t_worker	*workers;
	t_sync		sync;
	t_scene		*scene;
	t_canvas	*canvas;
	struct s_menu *menu;
	t_task		*queue;
}	t_render;

// Initialisation of threads

t_error	init_multithread(
	t_render *render,
	t_canvas canvas,
	t_scene *scene,
	t_menu menu);

t_error	fill_and_start_threads(t_render *render);

// Thread routine

void	*render_routine(void *data);

void	wait_jobs_finish(t_render *render);

// Task queue

t_task	*init_tasks_queue();

void	del_queue(t_task **queue);

void	push_task(t_task **queue, t_task *new_task, int *nb_task_remain);

t_task	*pop_task_lst(
	t_task **queue,
	pthread_mutex_t *queue_mutex,
	int *nb_tasks_remain,
	sem_t *jobs_sem);

void	reset_task_queue(t_render *render);

// Task

void	task_cast_ray(t_worker *worker, t_task *task);

t_task	*create_ray_task(
			t_ray *ray,
			int32_t ppr,
			double pix[2],
			int back_canvas);

// Mutex, semaphore and condition

void	del_mut_cond_sem(t_sync *sync);

// Threads

void	join_all_threads(t_worker *workers);

long	get_nb_threads();

#endif
