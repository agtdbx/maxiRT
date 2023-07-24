/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ray_from_pixel_coords.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:19:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 16:22:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <stdbool.h>
#include <stdint.h>

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/canvas/canvas_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

t_ray	create_ray_from_pixel_coords(
			t_camera const *camera,
			t_canvas const *canvas,
			int32_t const coords[2])
{
	t_ray	casted_ray;

	casted_ray.pos = camera->pos;
	casted_ray.vec = camera->pos;
	vec3_linear_transform(
		&casted_ray.vec, coords[0] - canvas->width_div_2, &camera->o_x);
	vec3_linear_transform(
		&casted_ray.vec, coords[1] - canvas->height_div_2, &camera->o_y);
	vec3_linear_transform(
		&casted_ray.vec, camera->focal, &camera->direction);
	vec3_substract(&casted_ray.vec, &casted_ray.pos);
	vec3_normalize(&casted_ray.vec);
	return (casted_ray);
}
