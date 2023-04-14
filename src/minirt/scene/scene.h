/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:03:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 01:25:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

//> SCENE MODEL
//>
//> Contains objects to be rendered by the raytracer.
//> Shall be filled with objects described in the config file
//> whose name has been given in parameters.

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

#endif//SCENE_H
