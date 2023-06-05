/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:35:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/05 09:39:03 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/menu/menu.h"
#include <minirt/app/app.h>

#include <MLX42/MLX42.h>
#include <stdio.h>
#include <math.h>

static inline void	_log_fps(
						mlx_t const *mlx);

static inline void	_limit_delta_time(
						mlx_t *mlx);

void	app_loop(void *const data)
{
	t_app *const	app = data;
	t_camera *const	camera = app->scene.camera;
	bool			should_render;

	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(app->mlx);
		return ;
	}
	_log_fps(app->mlx);
	_limit_delta_time(app->mlx);
	should_render = (false
		| handle_window_resizing(app->mlx, &app->canvas, camera, &app->menu)
		| handle_menu_toggling(app->mlx, &app->menu)
		| handle_translations(app->mlx, camera)
		| handle_rotations(app->mlx, &app->canvas, camera)
		| handle_mouse_clicks(app->mlx, &app->menu, &app->scene, &app->canvas));
	menu_draw(app->mlx, &app->menu);
	render_canvas(app, should_render);
}

/**
 * Ensure dt is less than 0.25s
 * @param[out] mlx
 */
static inline void	_limit_delta_time(
						mlx_t *mlx)
{
	mlx->delta_time = fmin(mlx->delta_time, 0.25);
}

/**
 * Log averaged fps to standard output (atmost once per second)
 * @param[in] app App handle.
 */
static inline void	_log_fps(
						mlx_t const *mlx)
{
	static double	elapsed_seconds = 0.0;
	static double	number_of_frames = 0;
	
	elapsed_seconds += mlx->delta_time;
	number_of_frames++;
	if (elapsed_seconds < 1.0)
		return ;
	printf("fps: %5.2f\n", number_of_frames / elapsed_seconds);
	elapsed_seconds = 0.0;
	number_of_frames = 0.0;
}
