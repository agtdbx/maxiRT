/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:36:44 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 14:40:27 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/render/multithread/multithread.h"

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

void	task_cast_ray(t_worker const *worker, t_task *task)
{
	mlx_image_t		*img;
	pthread_mutex_t	*img_mutex;
	int32_t			pixel_color;

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
	pixel_color = render_ray_from_camera(
		task,
		worker->render->scene,
		&worker->render->sync.scene_mut,
		worker->render->menu->is_visible
	);
	pthread_mutex_lock(img_mutex);
	if (!worker->render->sync.reset_render)
		img_draw_square(img, task->pixels, task->ppr, pixel_color);
	pthread_mutex_unlock(img_mutex);
	worker->render->sync.pixel_rendered += task->ppr;
}

t_task	*create_ray_task(
			t_ray const *ray,
			int32_t ppr,
			const int32_t pix[2],
			int back_canvas)
{
	t_task	*new_task;

	new_task = malloc(sizeof(t_task));
	if (new_task == NULL)
	{
		perror("Error\nFatal");
		return NULL;
	}
	ft_memset(new_task, 0, sizeof(t_task));
	new_task->ray = *ray;
	new_task->back_canvas = back_canvas;
	new_task->ppr = ppr;
	new_task->pixels[0] = pix[0];
	new_task->pixels[1] = pix[1];
	new_task->object = NULL;
	return new_task;
}
