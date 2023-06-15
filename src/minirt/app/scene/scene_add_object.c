/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:28:29 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 12:55:08 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "libft/libft.h"

static void	_object_add_back(
				t_object **objects,
				t_object *new_object);

t_error	scene_add_object(
			t_scene *scene,
			t_object *obj)
{
	t_object	*new_object;

	new_object = ft_memdup(obj, sizeof(t_object));
	if (new_object == NULL)
	{
		perror("Error\nFatal");
		return (FAILURE);
	}
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
