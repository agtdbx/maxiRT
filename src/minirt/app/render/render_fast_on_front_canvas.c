/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fast_on_front_canvas.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:52:18 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:54:08 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/render/multithread/multithread.h"

#define X 0
#define Y 1

static void	_get_top_left_ray(
				t_canvas const *canvas,
				t_camera const *camera,
				t_vec3 *top_left_vec);

t_error	render_fast_on_front_canvas(
			t_app *app,
			int32_t ppr)
{
	t_vec3	ray[2];
	double	pix[2];
	t_ray	casted_ray;
	t_task	*new_task;

	_get_top_left_ray(&app->canvas, app->scene->camera, &ray[Y]);
	casted_ray.pos = app->scene->camera->pos;
	pix[Y] = 0;
	while (pix[Y] < app->canvas.height)
	{
		ray[X] = ray[Y];
		pix[X] = 0;
		while (pix[X] < app->canvas.width)
		{
			casted_ray.depth = 0;
			vec3_normalize_into(&casted_ray.vec, &ray[X]);
			new_task = create_ray_task(&casted_ray, ppr, pix, 0);
			if (new_task == NULL)
				return FAILURE;
			push_task(
				&app->render.queue,
				new_task,
				&app->render.sync.nb_tasks_remain);
			vec3_linear_transform(&ray[X], ppr, &app->scene->camera->o_x);
			pix[X] += ppr;
		}
		vec3_linear_transform(&ray[Y], ppr, &app->scene->camera->o_y);
		pix[Y] += ppr;
	}
	app->render.sync.reset_render = false;
	sem_post(&app->render.sync.jobs_sem);
	wait_jobs_finish(&app->render);
	return SUCCESS;
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
