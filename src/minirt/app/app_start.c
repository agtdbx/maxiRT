/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:49:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/14 02:08:56 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <MLX42/MLX42.h>

#include <stdio.h>//TODO
#include <stddef.h>

//**** DECLARATIONS **********************************************************//

mlx_errno_t			app_start(void);
static mlx_errno_t	_create_mlx_images(t_app *const app);

//**** DEFINITIONS ***********************************************************//

mlx_errno_t	app_start(void)
{
	t_app	app;

	app.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (app.mlx == NULL)
	{
		fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
		return (mlx_errno);
	}
	if (_create_mlx_images(&app) != MLX_SUCCESS)
	{
		mlx_terminate(app.mlx);
		fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
		return (mlx_errno);
	}
	if (mlx_loop_hook(app.mlx, app_loop, &app) == false)
	{
		mlx_terminate(app.mlx);
		fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
		return (mlx_errno);
	}
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (MLX_SUCCESS);
}

static mlx_errno_t	_create_mlx_images(t_app *const app)
{
	app->canvas.front = mlx_new_image(
			app->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (app->canvas.front == NULL)
		return (mlx_errno);
	if (mlx_image_to_window(app->mlx, app->canvas.front, 0, 0) == -1)
		return (mlx_errno);
	// app->canvas.front->instances->z = 1;
	// app->canvas.back = mlx_new_image(
	// 		app->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// if (app->canvas.back == NULL)
	// 	return (mlx_errno);
	// if (mlx_image_to_window(app->mlx, app->canvas.back, 0, 0) == -1)
	// 	return (mlx_errno);
	//create second rendering_canvas
	//create_menu
	return (MLX_SUCCESS);
}
