/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:36:44 by damien            #+#    #+#             */
/*   Updated: 2025/01/11 10:53:39 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/render/multithread/multithread.h"

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

void	task_cast_ray(t_worker *worker, t_task *task)
{
	mlx_image_t		*img;
	pthread_mutex_t	*img_mutex;

	if (task->back_canvas == 1)
	{
		img = worker->render->canvas->back;
		img_mutex = &worker->render->sync.canvas_mut[BACK_CANVAS];
	}
	else
	{
		img = worker->render->canvas->front;
		img_mutex = &worker->render->sync.canvas_mut[FRONT_CANVAS];
	}
	img_draw_square(
		&worker->render->sync,
		img_mutex,
		img,
		task->pixels,
		task->ppr,
		render_ray_from_camera(
			worker->render->canvas,
			task,
			worker->render->scene,
			&worker->render->sync.scene_mut,
			worker->render->menu->is_visible
		)
	);
	worker->render->sync.pixel_rendered += task->ppr;
}

t_task	*create_ray_task(
			t_ray *ray,
			int32_t ppr,
			double pix[2],
			int back_canvas)
{
	t_task	*new_task;

	new_task = malloc(sizeof(t_task));
	if (new_task == NULL)
		return NULL;
	ft_memset(new_task, 0, sizeof(t_task));
	new_task->ray = *ray;
	new_task->back_canvas = back_canvas;
	new_task->ppr = ppr;
	new_task->pixels[0] = pix[0];
	new_task->pixels[1] = pix[1];
	new_task->object = NULL;
	return new_task;
}
