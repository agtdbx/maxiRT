/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:30:35 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:30:45 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/render/multithread/multithread.h"

void	join_all_threads(t_worker *workers)
{
	int		i;
	long	nb_threads;

	nb_threads = get_nb_threads();
	for (i = 0; i < nb_threads - 1; i++)
		sem_post(&workers[i].render->sync.jobs_sem);
	for (i = 0; i < nb_threads - 1; i++)
		pthread_join(workers[i].thid, NULL);
}
