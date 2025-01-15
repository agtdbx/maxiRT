/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:30:35 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/15 22:29:50 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <stddef.h>
#include <stdlib.h>

#include "libft/libft.h"

#define NB_CUBE_FACES 6

static void	loc_del_lights(
				t_light **lights);
static void	loc_del_objects(
				t_object **objects);

void	scene_del(
			t_scene *scene)
{
	int			i;
	t_object	*tmp;

	ft_memdel(&scene->camera);
	loc_del_lights(&scene->spotlights);
	loc_del_lights(&scene->ambient_lightning);
	tmp = scene->objects;
	while (tmp)
	{
		if (tmp->texture != NULL)
			mlx_delete_texture(tmp->texture);
		if (tmp->normal_map != NULL)
			mlx_delete_texture(tmp->normal_map);
		tmp = tmp->next;
	}
	loc_del_objects(&scene->objects);

	if (scene->skybox)
	{
		for (i = 0; i < NB_CUBE_FACES; i++)
			free(scene->skybox->value.as_skybox.textures[i].pixels);
		free(scene->skybox->value.as_skybox.textures);
		mlx_delete_texture(scene->skybox->texture);
		free(scene->skybox);
	}
	if (scene->planes != NULL)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
}

static void	loc_del_lights(
				t_light **lights)
{
	if (*lights == NULL)
		return ;
	loc_del_lights(&(*lights)->next);
	ft_memdel(lights);
}

static void	loc_del_objects(
				t_object **objects)
{
	if (*objects == NULL)
		return ;
	loc_del_objects(&(*objects)->next);
	if ((*objects)->type == OBJ_OBJECT_FILE)
	{
		free((*objects)->value.as_object_file.vertices);
		(*objects)->value.as_object_file.vertices = NULL;
		free((*objects)->value.as_object_file.real_vertices);
		(*objects)->value.as_object_file.real_vertices = NULL;
		free((*objects)->value.as_object_file.polygons);
		(*objects)->value.as_object_file.polygons = NULL;
		free_object_binary_tree((*objects)->value.as_object_file.binary_partition);
	}
	ft_memdel(objects);
}
