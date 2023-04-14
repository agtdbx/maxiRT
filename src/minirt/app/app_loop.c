/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:58:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 01:00:28 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include "MLX42/MLX42.h"

void	app_loop(void *const data)
{
	t_app *const	app = data;

	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(app->mlx);
		return ;
	}
}

// void	main_loop(void *const data)
// {
// 	t_app *const	app = data;
// 	static double	seconds_since_last_tick = 0;
// 	static ssize_t	rendered_columns = -1;
//
// 	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_close_window(app->mlx);
// 		return ;
// 	}
// 	if (process_inputs(app) == true)
// 	{
// 		rendered_columns = -1;
// 	}
// 	else if (0 <= rendered_columns && rendered_columns < WINDOW_WIDTH)
// 	{
// 		// render_high_res_column(app, rendered_columns);
// 		rendered_columns++;
// 	}
// 	else if (rendered_columns == WINDOW_WIDTH)
// 	{
// 		//swap_RenderingImages
// 	}
// 	
// 	// cap fps when moving
// 	seconds_since_last_tick += app->mlx->delta_time;
// 	if (seconds_since_last_tick < MINIMUM_RENDERING_TIMESTEP_IN_SECONDS)
// 	{
// 		return ;
// 	}
// 	printf("fps: %f\n", 1 / seconds_since_last_tick);
// 	seconds_since_last_tick = 0;
// 	if (rendered_columns == -1)
// 	{
// 		//render_low_res(app);
// 		rendered_columns++;
// 	}
// }
