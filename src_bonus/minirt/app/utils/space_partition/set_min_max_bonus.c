/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_min_max_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:03:18 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 12:03:59 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/utils/space_partition/space_partition.h"

void	set_min_max(
			float *min,
			float *max,
			float *test)
{
	if (*min > *test)
		*min = *test;
	if (*max < *test)
		*max = *test;
}
