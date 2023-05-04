/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_camera.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:20:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 15:43:41 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_CAMERA_H
# define SCENE_CAMERA_H

//> SCENE'S CAMERA MODEL
//>
//> `direction' stands for where the camera looks at
//> `o_x' and `o_y' stand for the basis of the screen vector space

# include <minirt/utils/color.h>
# include <minirt/utils/geometry.h>

typedef struct s_camera
{
	float	fov;
	t_vec3	pos;

	t_vec3	direction;
	t_vec3	o_x;
	t_vec3	o_y;
	float	focal;
}	t_camera;

#endif//SCENE_CAMERA_H
