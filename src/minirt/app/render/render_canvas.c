/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_canvas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2024/12/26 16:12:16 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/app.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/utils/geometry/geometry.h"

static void	_print_rendering_progress(
				int pixel_rendered,
				mlx_t *mlx,
				bool is_rendering);
static void	_update_ppr(
				double delta_time,
				int32_t *ppr);
static bool	_is_under_10_fps(
				double delta_time);
static bool	_is_over_25_fps(
				double delta_time);

void	render_canvas(
			t_app *app,
			bool should_render_fast)
{
	static int32_t	task_created = 0;
	static int32_t	pixel_per_ray = 16;
	static bool		is_rendering = false;

	if (app->render.sync.constant_calculated != 1)
		return ;
	if (should_render_fast)
	{
		if (app->render.sync.nb_tasks_remain != 0)
		{
			// We were generating back canvas when user moved
			sem_init(&app->render.sync.jobs_sem, 0, 0);
			pthread_mutex_lock(&app->render.sync.queue_mut);
			app->render.sync.nb_tasks_remain = 0;
			del_queue(&app->render.queue);
			pthread_mutex_unlock(&app->render.sync.queue_mut);
		}
		if (is_rendering)
			_update_ppr(app->mlx->delta_time, &pixel_per_ray);
		if (render_fast_on_front_canvas(app, pixel_per_ray) == FAILURE)
		{
			del_queue(&app->render.queue);
			free(app->render.workers);
			sem_init(&app->render.sync.jobs_sem, 0, 0);
			app->render.sync.keep_alive = 0;
			return ;
		}
		is_rendering = true;
		task_created = 0;
		app->render.sync.pixel_rendered = 0;
		return ;
	}
	_print_rendering_progress(app->render.sync.pixel_rendered, app->mlx, is_rendering);
	if (is_rendering)
	{
		task_created += render_next_pixels_til_tmax_on_back_canvas(app, task_created);
		if (app->render.sync.nb_tasks_remain == 0)
		{
			canvas_swap(&app->canvas);
			is_rendering = false;
		}
	}
}

static void	_print_rendering_progress(
				int pixel_rendered,
				mlx_t *mlx,
				bool is_rendering)
{
	static mlx_image_t	*img = NULL;
	float				progress_rate;
	char				str[30];
	size_t				len;

	if (img != NULL)
	{
		mlx_delete_image(mlx, img);
		img = NULL;
	}
	if (!is_rendering)
		return ;
	progress_rate = pixel_rendered;
	progress_rate *= 100.0f / (mlx->width * mlx->height);
	len = ft_sitoa(progress_rate, str, sizeof(str));
	ft_strlcpy(str + len, " %", sizeof(str) - len);
	img = mlx_put_string(mlx, str, 10, 10);
	mlx_set_instance_depth(img->instances, 3);
}

/**
 * auto update ppr according to last dt
 * @param[in] mlx
 * @param[out] ppr
 */
static inline void	_update_ppr(
						double delta_time,
						int32_t *ppr)
{
	if (_is_under_10_fps(delta_time) && *ppr < 25)
	{
		++(*ppr);
	}
	if (_is_over_25_fps(delta_time) && 1 < *ppr)
	{
		--(*ppr);
	}
}

static bool	_is_under_10_fps(
				double delta_time)
{
	return (0.1 < delta_time);
}

static bool	_is_over_25_fps(
				double delta_time)
{
	return (delta_time < 0.04);
}
