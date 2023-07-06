/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:39:03 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/06 14:33:20 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/debug/debug.h>

#include <stdbool.h>

#include "minirt/app/app.h"

#include <stdint.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"

bool	g_is_debugging = false;

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
