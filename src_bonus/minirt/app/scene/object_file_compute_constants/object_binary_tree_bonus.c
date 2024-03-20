/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_binary_tree_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:38:22 by auguste           #+#    #+#             */
/*   Updated: 2024/03/20 21:39:01 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <stdlib.h>

void	create_new_object_binary_tree_part(
			t_object_binary_part **new)
{
	*new = malloc(sizeof(t_object_binary_part));

	if (*new == NULL)
	{
		*new = NULL;
		return ;
	}

	(*new)->child_1 = NULL;
	(*new)->child_2 = NULL;
	(*new)->polygons = NULL;
}

void	free_object_binary_tree(
			t_object_binary_part *part)
{
	if (part == NULL)
		return ;

	free_object_binary_polygons(part->polygons);

	free_object_binary_tree(part->child_1);
	free_object_binary_tree(part->child_2);

	free(part);
}


void	add_object_binary_polygons(
			t_object_binary_polygon **polygons,
			t_object_polygon *new_polygon,
			int polygon_id)
{
	t_object_binary_polygon *new;
	t_object_binary_polygon *actual;

	new = malloc(sizeof(t_object_binary_polygon));
	if (new == NULL)
		return ;

	new->next = NULL;
	new->polygon = new_polygon;
	new->polygon_id = polygon_id;

	if (*polygons == NULL)
	{
		*polygons = new;
		return ;
	}

	actual = *polygons;
	while (actual->next != NULL)
		actual = actual->next;

	actual->next = new;
}


void	free_object_binary_polygons(
			t_object_binary_polygon *polygon)
{
	t_object_binary_polygon *next;

	while (polygon != NULL)
	{
		next = polygon->next;
		free(polygon);
		polygon = next;
	}
}
