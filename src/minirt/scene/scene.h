/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:03:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/01 23:59:41 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

//> SCENE MODEL
//>
//> Contains objects to be rendered by the raytracer.
//> Shall be filled with objects described in the config file
//> whose name has been given in parameters.

# include <libft/libft.h>

# include <minirt/scene/scene_light.h>
# include <minirt/scene/scene_object.h>
# include <minirt/scene/scene_camera.h>

typedef struct s_scene
{
	t_object	*objects;
	t_light		*spotlights;
	t_light		*ambient_lightning;
	t_camera	*camera;
}	t_scene;

t_error	scene_add_object(
			t_scene *scene,
			t_object_t type,
			void const *value);

void	scene_del(
			t_scene *scene);

#endif//SCENE_H
