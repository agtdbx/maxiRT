/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:35:45 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:52:36 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "MLX42/MLX42.h"

#include "minirt/app/menu/menu.h"
#include "minirt/app/encode/encode.h"

static inline bool	_handle_user_inputs(
						t_app *app);
static inline void	_log_fps(
						mlx_t const *mlx);
static inline void	_limit_delta_time(
						mlx_t *mlx);

/**
 * the main loop hook
 * @param[in] data - the app handle
 */
void	app_loop(
			void *const data)
{
	t_app *const	app = data;
	bool			should_render;

	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(app->mlx);
		return ;
	}
	_log_fps(app->mlx);
	_limit_delta_time(app->mlx);
	should_render = false;
	should_render |= _handle_user_inputs(app);
	should_render |= menu_draw(app->mlx, &app->menu, &app->canvas,
			&app->render.sync.scene_mut, app->scene);
	if (app->encoder.is_recording
		&& encode_frame(app->canvas.front, &app->encoder) == FAILURE)
		mlx_close_window(app->mlx);
	if (render_canvas(app, should_render) == FAILURE)
		mlx_close_window(app->mlx);
}

/**
 * run input handlers in order
 * @param[in] app - the app handle
 * @returns Wether canvas should be rerendered
 */
static inline bool	_handle_user_inputs(
						t_app *app)
{
	bool	should_render;
	t_error	err;

	err = SUCCESS;
	should_render = false;
	handle_recording(
		app->mlx,
		app->canvas.render_icon,
		&app->encoder,
		&err);
	if (err == FAILURE)
		return (should_render);
	should_render |= handle_window_resizing(
			app->mlx, &app->menu, app->scene,
			&app->canvas, &app->render.sync);
	if (should_render && app->encoder.is_recording)
		close_recording(&app->encoder, app->canvas.render_icon, app->mlx->width, app->mlx->height);
	should_render |= handle_menu_toggling(
			app->mlx, &app->menu);
	should_render |= handle_translations(
			app->mlx, app->scene->camera);
	should_render |= handle_rotations(
			app->mlx, &app->canvas, app->scene->camera);
	handle_mouse_clicks(app->mlx, &app->menu, app->scene, &app->canvas);
	return (should_render);
}

/**
 * Ensure dt is less than 0.25s
 * @param[out] mlx
 */
static inline void	_limit_delta_time(
						mlx_t *mlx)
{
	mlx->delta_time = fmin(mlx->delta_time, 0.5);
}

/**
 * Log averaged fps to standard output (atmost once per second)
 * @param[in] app App handle.
 */
static inline void	_log_fps(
						mlx_t const *mlx)
{
	static double	elapsed_seconds = 0.0;
	static double	number_of_frames = 0.0;

	elapsed_seconds += mlx->delta_time;
	number_of_frames++;
	if (elapsed_seconds < 1.0)
		return ;
	printf("fps: %5.2f\n", number_of_frames / elapsed_seconds);
	elapsed_seconds = 0.0;
	number_of_frames = 0.0;
}
