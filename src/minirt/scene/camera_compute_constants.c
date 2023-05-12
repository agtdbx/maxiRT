/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_compute_constants.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/12 17:31:55 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/scene/scene_camera.h>

#include <minirt/utils/geometry.h>
#include <MLX42/MLX42.h>
#include <math.h>

//TODO(tdubois): calculer tanf seulement quand la fov est modifiée

/**
 * Compute constants from camera properties to facilitate further calculations
 * @param[in] mlx
 * @param[out] camera
 */
void	camera_compute_constants(
			mlx_t const *mlx,
			t_camera *camera)
{
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
	camera->focal = mlx->width / (2.0f * tanf(camera->fov * PI_DIV_360));
}
