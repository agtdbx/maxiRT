/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_compute_constants.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 16:04:18 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/scene/scene.h"

#include <math.h>

#include "MLX42/MLX42.h"

#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"

//TODO(tdubois): calculer tanf seulement quand la fov est modifiée

/**
 * Compute constants from camera properties to facilitate further calculations
 * @param[in] canvas
 * @param[out] camera
 */
void	camera_compute_constants(
			t_canvas const *canvas,
			t_camera *camera)
{
	vec3_normalize(&camera->direction);
	camera->o_x = vec3(
			- camera->direction.z,
			0.0f,
			+ camera->direction.x);
	vec3_normalize(&camera->o_x);
	camera->o_y = vec3(
			+ camera->direction.x * camera->direction.y,
			- powf(camera->direction.x, 2.0f) - powf(camera->direction.z, 2.0f),
			+ camera->direction.y * camera->direction.z);
	vec3_normalize(&camera->o_y);
	camera->focal = canvas->width_div_2 / tanf(camera->fov * g_pi_div_360);
}
