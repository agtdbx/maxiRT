/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mut_cond_sem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:31:34 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:32:01 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/render/multithread/multithread.h"

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

void	del_mut_cond_sem(t_sync *sync)
{
	pthread_mutex_destroy(&sync->queue_mut);
	pthread_mutex_destroy(&sync->canvas_mut[FRONT_CANVAS]);
	pthread_mutex_destroy(&sync->canvas_mut[BACK_CANVAS]);
	pthread_mutex_destroy(&sync->active_threads_mut);
	pthread_cond_destroy(&sync->finish_jobs_cond);
	sem_destroy(&sync->jobs_sem);
}
