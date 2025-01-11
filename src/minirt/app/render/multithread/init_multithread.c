/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multithread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:59:27 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:57:18 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/render/multithread/multithread.h"

#include "libft/libft.h"

#include <stdlib.h>

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

static t_error	_init_mutex_cond_sem(t_render *render);
static t_error	_start_threads(t_render *render, long nb_threads);

t_error	init_multithread(
	t_render *render,
	t_canvas canvas,
	t_scene *scene,
	t_menu menu)
{
	long	nb_threads;

	nb_threads = get_nb_threads();
	render->workers = malloc((nb_threads - 1) * sizeof(t_worker));
	if (render->workers == NULL)
	{
		free(render->queue);
		return FAILURE;
	}
	if (_init_mutex_cond_sem(render) == FAILURE)
	{
		free(render->queue);
		free(render->workers);
		return FAILURE;
	}
	render->queue = NULL;
	render->sync = (t_sync){
		.nb_active_threads = 0,
		.nb_tasks_remain = 0,
		.pixel_rendered = 0,
		.keep_alive = 1,
	};
	render->canvas = &canvas;
	render->scene = scene;
	render->menu = &menu;
	return SUCCESS;
}

t_error	fill_and_start_threads(t_render *render)
{
	int		i;
	long	nb_threads;

	nb_threads = get_nb_threads();
	for (i = 0; i < nb_threads - 1; i++)
		render->workers[i].render = render;
	return _start_threads(render, nb_threads);
}

static t_error	_start_threads(t_render *render, long nb_threads)
{
	int				i;
	pthread_attr_t	attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (i = 0; i < nb_threads - 1; i++)
	{
		if (pthread_create(&render->workers[i].thid, &attr,
				render_routine, &render->workers[i]) != 0)
		{
			for (; i >= 0; i--)
				pthread_join(render->workers[i].thid, NULL);
			pthread_attr_destroy(&attr);
			return FAILURE;
		}
	}
	pthread_attr_destroy(&attr);
	return SUCCESS;
}


static t_error	_init_mutex_cond_sem(t_render *render)
{
	if (pthread_mutex_init(&render->sync.queue_mut, NULL) != 0 ||
		pthread_mutex_init(&render->sync.canvas_mut[FRONT_CANVAS], NULL) != 0 ||
		pthread_mutex_init(&render->sync.canvas_mut[BACK_CANVAS], NULL) != 0 ||
		pthread_mutex_init(&render->sync.active_threads_mut, NULL) != 0)
	{
		perror("pthread_mutex_init() error");
		return FAILURE;
	}
	if (pthread_rwlock_init(&render->sync.scene_mut, NULL))
	{
		perror("pthread_rwlock_init() error");
		return FAILURE;
	}
	if (pthread_cond_init(&render->sync.finish_jobs_cond, NULL) != 0)
	{
		perror("pthread_cond_init() error");
		return FAILURE;
	}
	if (sem_init(&render->sync.jobs_sem, 0, 0) != 0)
	{
		perror("sem_init() error");
		return FAILURE;
	}
	return SUCCESS;
}
