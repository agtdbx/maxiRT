/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fast_on_front_canvas.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:52:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/18 18:24:07 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/drawings/drawings.h"

#define X 0
#define Y 1

static void	_get_top_left_ray(
				t_canvas const *canvas,
				t_camera const *camera,
				t_vec3 *top_left_vec);

void	render_fast_on_front_canvas(
			t_app *app,
			int32_t ppr)
{
	t_vec3			ray[2];
	int32_t			pix[2];
	t_ray			casted_ray;

	_get_top_left_ray(&app->canvas, app->scene.camera, &ray[Y]);
	casted_ray.pos = app->scene.camera->pos;
	pix[Y] = 0;
	while (pix[Y] < app->canvas.height)
	{
		ray[X] = ray[Y];
		pix[X] = 0;
		while (pix[X] < app->canvas.width)
		{
			casted_ray.depth = 0;
			vec3_normalize_into(&casted_ray.vec, &ray[X]);
			img_draw_square(app->canvas.front, pix, ppr, render_ray_from_camera(
					&app->scene, &casted_ray, app->menu.is_visible));
			vec3_linear_transform(&ray[X], ppr, &app->scene.camera->o_x);
			pix[X] += ppr;
		}
		vec3_linear_transform(&ray[Y], ppr, &app->scene.camera->o_y);
		pix[Y] += ppr;
	}
}

/**
 *  Compute the direction of the ray associated with the topleft corner pixel.
 *  @param[in] mlx The mlx harness
 *  @param[in] camera The camera instance
 *  @param[out] top_left The un-normalized computed ray
 */
static void	_get_top_left_ray(
				t_canvas const *canvas,
				t_camera const *camera,
				t_vec3 *top_left_vec)
{
	*top_left_vec = camera->pos;
	vec3_linear_transform(top_left_vec, -canvas->width_div_2, &camera->o_x);
	vec3_linear_transform(top_left_vec, -canvas->height_div_2, &camera->o_y);
	vec3_linear_transform(top_left_vec, camera->focal, &camera->direction);
	vec3_substract(top_left_vec, &camera->pos);
}
