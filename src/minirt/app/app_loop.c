/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:35:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 17:57:44 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <MLX42/MLX42.h>
#include <stdio.h>

static void	_log_fps(
				mlx_t *mlx);

void	app_loop(void *const data)
{
	t_app *const	app = data;
	bool			should_render;

	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(app->mlx);
		return ;
	}
	_log_fps(app->mlx);
	should_render = false;
	// should_render |= update_image_size(app->mlx)
	should_render |= update_camera_position(app->mlx, app->scene.camera);
	should_render |= update_camera_direction(app->mlx, app->scene.camera);
	// should_render |= update_scene(app);
	render(app->mlx, &app->canvas, &app->scene, should_render);
}

/**
 * Log averaged fps to standard output (atmost once per second)
 * @param[in] app App handle.
 */
static void	_log_fps(
				mlx_t *mlx)
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
