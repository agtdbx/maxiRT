/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:28:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/02 09:28:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene/scene.h>
#include <libft/libft.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_error	scene_add_object(
			t_scene *scene,
			t_object_t type,
			void const *value);

static void	_object_add_back(
				t_object **objects,
				t_object *new_object);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_error	scene_add_object(
			t_scene *scene,
			t_object_t type,
			void const *value)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (new_object == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
	new_object->type = type;
	new_object->value = *((t_object_v *)value);
	new_object->next = NULL;
	_object_add_back(&scene->objects, new_object);
	return (SUCCESS);
}

static void	_object_add_back(
				t_object **objects,
				t_object *new_object)

{
	if (*objects == NULL)
		*objects = new_object;
	else
		_object_add_back(&(*objects)->next, new_object);
}
