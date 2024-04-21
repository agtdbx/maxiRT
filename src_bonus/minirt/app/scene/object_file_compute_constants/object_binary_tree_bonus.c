/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_binary_tree_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:38:22 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 13:15:09 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <stdlib.h>

void	create_new_object_binary_tree_part(
			t_object_binary_part **new,
			int nb_polygons_parent)
{
	int	i;

	*new = malloc(sizeof(t_object_binary_part));

	if (*new == NULL)
	{
		*new = NULL;
		return ;
	}

	(*new)->child_1 = NULL;
	(*new)->child_2 = NULL;
	(*new)->polygons = malloc(sizeof(t_object_binary_polygon) * (nb_polygons_parent + 1));
	if ((*new)->polygons == NULL)
	{
		free(*new);
		*new = NULL;
		return ;
	}

	i = 0;
	while (i < nb_polygons_parent)
	{
		(*new)->polygons[i].polygon_id = -1;
		(*new)->polygons[i].polygon = NULL;
		i++;
	}
	(*new)->polygons[i].polygon_id = -1;
	(*new)->polygons[i].polygon = NULL;
}

void	free_object_binary_tree(
			t_object_binary_part *part)
{
	if (part == NULL)
		return ;

	if (part->polygons)
		free(part->polygons);

	free_object_binary_tree(part->child_1);
	free_object_binary_tree(part->child_2);

	free(part);
}


void	add_object_binary_polygons(
			t_object_binary_polygon *polygons,
			t_object_polygon *new_polygon,
			int polygon_id,
			int nb_polygons_parent)
{
	int	i;

	i = 0;
	while (i < nb_polygons_parent)
	{
		if (polygons[i].polygon_id == -1)
		{
			polygons[i].polygon = new_polygon;
			polygons[i].polygon_id = polygon_id;
			return ;
		}
		i++;
	}
}
