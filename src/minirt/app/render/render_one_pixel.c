/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_one_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:06:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:59:53 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <stdint.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"

void	render_one_pixel(
			t_scene const *scene,
			t_canvas const *canvas,
			int32_t pixel_index,
			bool show_spotlights)
{
	t_ray			casted_ray;
	int32_t const	x = pixel_index % canvas->width;
	int32_t const	y = pixel_index / canvas->width;

	casted_ray.pos = scene->camera->pos;
	casted_ray.vec = scene->camera->pos;
	vec3_linear_transform(
		&casted_ray.vec, canvas->width_div_2 - x, &scene->camera->o_x);
	vec3_linear_transform(
		&casted_ray.vec, canvas->height_div_2 - y, &scene->camera->o_y);
	vec3_linear_transform(
		&casted_ray.vec, scene->camera->focal, &scene->camera->direction);
	vec3_substract(&casted_ray.vec, &casted_ray.pos);
	vec3_normalize(&casted_ray.vec);
	if (x < canvas->width && y < canvas->height)
		mlx_put_pixel(canvas->back, x, y,
			render_ray_from_camera(scene, &casted_ray, show_spotlights));
}
