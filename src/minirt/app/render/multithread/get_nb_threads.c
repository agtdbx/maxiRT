/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:29:35 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:57:25 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/render/multithread/multithread.h"

#include <unistd.h>

long	get_nb_threads()
{
	static long	nb_threads = 0;

	if (nb_threads == 0)
		nb_threads = sysconf(_SC_NPROCESSORS_ONLN);
	return (nb_threads);
}
