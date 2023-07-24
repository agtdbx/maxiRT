/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:30:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/05 13:01:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <stddef.h>

#include "libft/libft.h"

static void	loc_del_lights(
				t_light **lights);
static void	loc_del_objects(
				t_object **objects);

void	scene_del(
			t_scene *scene)
{
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
	ft_memdel(objects);
}
