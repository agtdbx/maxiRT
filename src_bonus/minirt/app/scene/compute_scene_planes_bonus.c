/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_scene_planes_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:23:41 by gugus             #+#    #+#             */
/*   Updated: 2024/06/15 22:40:24 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <stdlib.h>
#include <stdio.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

void	compute_scene_planes(
			t_scene *scene)
{
	int			nb_planes;
	t_object	*actual;

	scene->planes = NULL;

	nb_planes = 0;
	actual = scene->objects;

	while(actual)
	{
		if (actual->type == OBJ_PLANE)
			nb_planes++;
		actual = actual->next;
	}

	if (nb_planes == 0)
		return ;

	scene->planes = malloc(sizeof(t_object *) * (nb_planes + 1));
	if (scene->planes == NULL)
		return ;

	nb_planes = 0;
	actual = scene->objects;
	while(actual)
	{
		if (actual->type == OBJ_PLANE)
		{
			scene->planes[nb_planes] = actual;
			nb_planes++;
		}
		actual = actual->next;
	}
	scene->planes[nb_planes] = NULL;
}
