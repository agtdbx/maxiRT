/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:39:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/20 16:57:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/debug/debug.h>

#include <stdbool.h>

bool	g_is_debugging = false;

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"

void	render_one_pixel(
			t_scene const *scene,
			t_canvas const *canvas,
			int32_t const coords[2],
			bool show_spotlights)
{
	int32_t	color;
	t_ray	casted_ray;

	if (canvas->width <= coords[0] || canvas->height <= coords[1])
	{
		return ;
	}
	casted_ray.pos = scene->camera->pos;
	casted_ray.vec = scene->camera->pos;
	vec3_linear_transform(
		&casted_ray.vec, canvas->width_div_2 - coords[0], &scene->camera->o_x);
	vec3_linear_transform(
		&casted_ray.vec, canvas->height_div_2 - coords[1], &scene->camera->o_y);
	vec3_linear_transform(
		&casted_ray.vec, scene->camera->focal, &scene->camera->direction);
	vec3_substract(&casted_ray.vec, &casted_ray.pos);
	vec3_normalize(&casted_ray.vec);
	color = render_ray_from_camera(scene, &casted_ray, show_spotlights);
	mlx_put_pixel(canvas->back, coords[0], coords[1], color);
}

