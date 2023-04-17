/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:30:35 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 10:31:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene/scene.h>
#include <libft/libft.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

void		scene_del(
				t_scene *scene);

static void	loc_del_lights(
				t_light **lights);

static void	loc_del_objects(
				t_object **objects);

//############################################################################//
//#### DEFINITIONS ###########################################################//

void	scene_del(
			t_scene *scene)
{
	ft_memdel(&scene->camera);
	loc_del_lights(&scene->spotlights);
	loc_del_lights(&scene->ambient_lightning);
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
