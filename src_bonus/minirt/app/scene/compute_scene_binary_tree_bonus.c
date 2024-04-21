/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_scene_binary_tree_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:01:40 by auguste           #+#    #+#             */
/*   Updated: 2024/04/21 18:37:50 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene_bonus.h"

#include <stdlib.h>

#include "minirt/app/utils/geometry/geometry_bonus.h"
#include "minirt/app/utils/space_partition/space_partition.h"

#define MIN_SIZE_SCENE_BBOX 100.0f

static t_scene_binary_part	*_create_scene_binary_part(
								int nb_object);
static void					_add_object_to_objects(
								t_object **objects,
								t_object *object,
								int nb_objects);
static void					_compute_scene_binary_part(
								t_scene_binary_part *parent,
								int nb_objects_parent);
static bool					_is_bbox_too_small(
								t_bounding_box *bbox);

void	free_scene_binary_tree(
			t_scene_binary_part *part)
{
	if (part == NULL)
		return ;

	if (part->objects)
		free(part->objects);

	free_scene_binary_tree(part->child_1);
	free_scene_binary_tree(part->child_2);

	free(part);
}

void	compute_scene_binary_tree(
			t_scene *scene)
{
	t_object	*iterator;
	int			nb_objects;

	if (scene->binary_tree != NULL)
	{
		free_scene_binary_tree(scene->binary_tree);
		scene->binary_tree = NULL;
	}

	nb_objects = 0;
	iterator = scene->objects;
	while (iterator)
	{
		// if (iterator->type != OBJ_PLANE)
		nb_objects++;
		iterator = iterator->next;
	}
	if (nb_objects == 0)
		return ;

	scene->binary_tree = _create_scene_binary_part(nb_objects);
	if (scene->binary_tree == NULL)
		return ;

	iterator = scene->objects;
	scene->binary_tree->bounding_box.min_x = g_scene_radius;
	scene->binary_tree->bounding_box.max_x = -g_scene_radius;
	scene->binary_tree->bounding_box.min_y = g_scene_radius;
	scene->binary_tree->bounding_box.max_y = -g_scene_radius;
	scene->binary_tree->bounding_box.min_z = g_scene_radius;
	scene->binary_tree->bounding_box.max_z = -g_scene_radius;
	while (iterator)
	{
		// if (iterator->type == OBJ_PLANE)
		// {
		// 	iterator = iterator->next;
		// 	continue;
		// }
		_add_object_to_objects(
			scene->binary_tree->objects,
			iterator, nb_objects);
		if (iterator->bounding_box.min_x < scene->binary_tree->bounding_box.min_x)
			scene->binary_tree->bounding_box.min_x = iterator->bounding_box.min_x;
		if (iterator->bounding_box.max_x > scene->binary_tree->bounding_box.max_x)
			scene->binary_tree->bounding_box.max_x = iterator->bounding_box.max_x;
		if (iterator->bounding_box.min_y < scene->binary_tree->bounding_box.min_y)
			scene->binary_tree->bounding_box.min_y = iterator->bounding_box.min_y;
		if (iterator->bounding_box.max_y > scene->binary_tree->bounding_box.max_y)
			scene->binary_tree->bounding_box.max_y = iterator->bounding_box.max_y;
		if (iterator->bounding_box.min_z < scene->binary_tree->bounding_box.min_z)
			scene->binary_tree->bounding_box.min_z = iterator->bounding_box.min_z;
		if (iterator->bounding_box.max_z > scene->binary_tree->bounding_box.max_z)
			scene->binary_tree->bounding_box.max_z = iterator->bounding_box.max_z;
		iterator = iterator->next;
	}

	compute_bounding_box_constants(&scene->binary_tree->bounding_box);

	_compute_scene_binary_part(scene->binary_tree, nb_objects);
}


static t_scene_binary_part	*_create_scene_binary_part(
								int nb_object)
{
	int					i;
	t_scene_binary_part	*new;

	new = malloc(sizeof(t_scene_binary_part));
	if (new == NULL)
		return (NULL);

	new->objects = malloc(sizeof(t_object *) * (nb_object + 1));
	if (new->objects == NULL)
	{
		free(new);
		return (NULL);
	}

	new->child_1 = NULL;
	new->child_2 = NULL;

	i = 0;
	while (i < nb_object)
	{
		new->objects[i] = NULL;
		i++;
	}
	new->objects[i] = NULL;

	return (new);
}

static void	_add_object_to_objects(
				t_object **objects,
				t_object *object,
				int nb_objects)
{
	int	i;

	i = 0;
	while (i < nb_objects)
	{
		if (objects[i] == NULL)
		{
			objects[i] = object;
			return ;
		}
		i++;
	}
}

#include <stdio.h>
static void	_compute_scene_binary_part(
				t_scene_binary_part *parent,
				int nb_objects_parent)
{
	int					i;
	int					nb_objects_child1;
	int					nb_objects_child2;
	t_scene_binary_part	*child_1;
	t_scene_binary_part	*child_2;

	printf("\nbbox : %i objects\n"
			"       x (%+7.3f %+7.3f)\n"
			"       y (%+7.3f %+7.3f)\n"
			"       z (%+7.3f %+7.3f)\n",
			nb_objects_parent,
			parent->bounding_box.min_x,
			parent->bounding_box.max_x,
			parent->bounding_box.min_y,
			parent->bounding_box.max_y,
			parent->bounding_box.min_z,
			parent->bounding_box.max_z);
	if (nb_objects_parent < 10
		|| _is_bbox_too_small(&parent->bounding_box))
	{
		printf("stop\n");
		return ;
	}
	printf("split in 2\n");


	child_1 = _create_scene_binary_part(nb_objects_parent);
	if (child_1 == NULL)
		return ;
	child_2 = _create_scene_binary_part(nb_objects_parent);
	if (child_2 == NULL)
	{
		free(child_1);
		return ;
	}

	// Cut main bbox in half by axe to childs have bbox
	compute_childs_bbox(
		&parent->bounding_box,
		&child_1->bounding_box,
		&child_2->bounding_box);

	// Compute bbox constants for childs
	compute_bounding_box_constants(&child_1->bounding_box);
	compute_bounding_box_constants(&child_2->bounding_box);

	i = 0;
	nb_objects_child1 = 0;
	nb_objects_child2 = 0;

	// Iterate thought each objects of parent tree part
	while (i < nb_objects_parent)
	{
		if (is_bbox_in_bbox(
				&child_1->bounding_box, &parent->objects[i]->bounding_box))
		{
			_add_object_to_objects(
				child_1->objects, parent->objects[i], nb_objects_parent);
			nb_objects_child1++;
		}

		if (is_bbox_in_bbox(
				&child_2->bounding_box, &parent->objects[i]->bounding_box))
		{
			_add_object_to_objects(
				child_2->objects, parent->objects[i], nb_objects_parent);
			nb_objects_child2++;
		}

		i++;
	}

	// Free the useless polygons chain list (now polygons are in childs)
	free(parent->objects);
	parent->objects = NULL;

	parent->child_1 = child_1;
	parent->child_2 = child_2;

	_compute_scene_binary_part(child_1, nb_objects_child1);
	_compute_scene_binary_part(child_2, nb_objects_child2);
}

static bool	_is_bbox_too_small(
				t_bounding_box *bbox)
{
	return ((bbox->max_x - bbox->min_x) < MIN_SIZE_SCENE_BBOX
		|| (bbox->max_y - bbox->min_y) < MIN_SIZE_SCENE_BBOX
		|| (bbox->max_z - bbox->min_z) < MIN_SIZE_SCENE_BBOX);
}
