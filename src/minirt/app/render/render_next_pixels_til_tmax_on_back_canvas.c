/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_pixels_til_tmax_on_back_canvas.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:56:46 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/11 10:40:34 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"
#include "minirt/app/render/multithread/multithread.h"

int32_t	render_next_pixels_til_tmax_on_back_canvas(
			t_app *app,
			int32_t pixel_rendered)
{
	double			tmax;
	double			pixel_coords[2];
	int32_t			new_pixel_rendered;
	t_ray				casted_ray;
	t_task			*new_task;
	int					value;

	new_pixel_rendered = 0;
	pixel_coords[0] = pixel_rendered % app->canvas.width;
	pixel_coords[1] = pixel_rendered / app->canvas.width;
	tmax = mlx_get_time() - app->mlx->delta_time + 0.15;
	while (pixel_coords[1] < app->canvas.height)
	{
		while (pixel_coords[0] < app->canvas.width)
		{
			casted_ray = create_ray_from_pixel_coords(app->scene->camera,
				&app->canvas, pixel_coords);
			casted_ray.depth = 0;
			new_task = create_ray_task(&casted_ray, 1, pixel_coords, 1);
			if (new_task == NULL)
				return FAILURE;
			pthread_mutex_lock(&app->render.sync.queue_mut);
			push_task(
				&app->render.queue,
				new_task,
				&app->render.sync.nb_tasks_remain);
			pthread_mutex_unlock(&app->render.sync.queue_mut);
			++new_pixel_rendered;
			if (mlx_get_time() > tmax)
			{
				sem_getvalue(&app->render.sync.jobs_sem, &value);
				if (value == 0)
					sem_post(&app->render.sync.jobs_sem);
				return (new_pixel_rendered);
			}
			pixel_coords[0] += 1;
		}
		pixel_coords[1] += 1;
		pixel_coords[0] = 0;
	}
	return (new_pixel_rendered);
}
