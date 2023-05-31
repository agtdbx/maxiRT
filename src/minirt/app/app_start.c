/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:49:18 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 10:01:22 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/scene/scene.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static t_error	_app_init(
					t_app *app,
					t_scene *scene);
static void		_compute_constants(
					mlx_t const *mlx,
					t_canvas *canvas,
					t_scene *scene,
					t_menu *menu);

t_error	app_start(
			t_scene *scene)
{
	t_app	app;

	errno = 0;
	mlx_errno = 0;
	if (_app_init(&app, scene) == SUCCESS)
	{
		render(app.mlx, &app.canvas, &app.scene, true);
		mlx_loop(app.mlx);
		//cleanup
		return (SUCCESS);
	}
	if (mlx_errno != MLX_SUCCESS)
		printf("Error\n%s\n", mlx_strerror(mlx_errno));
	else if (errno != 0)
		printf("Error\n%s\n", strerror(errno));
	else
		printf("Error\nFatal, unknown error\n");
	return (FAILURE);
}

static t_error	_app_init(
					t_app *app,
					t_scene *scene)
{
	app->scene = *scene;
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (app->mlx == NULL)
		return (FAILURE);
	if (canvas_init(app->mlx, &app->canvas) == FAILURE)
	{
		mlx_terminate(app->mlx);
		return (FAILURE);
	}
	if (menu_init(app->mlx, &app->menu, &app->scene) == FAILURE)
	{
		mlx_terminate(app->mlx);
		return (FAILURE);
	}
	if (mlx_loop_hook(app->mlx, app_loop, app) == false)
	{
		mlx_terminate(app->mlx);
		// menu_del();
		return (FAILURE);
	}
	_compute_constants(app->mlx, &app->canvas, &app->scene, &app->menu);
	return (SUCCESS);
}

static void	_compute_constants(
				mlx_t const *mlx,
				t_canvas *canvas,
				t_scene *scene,
				t_menu *menu)
{
	t_object	*object_iterator;

	// camera_compute_constants(mlx, scene->camera);//TODO(tdubois)
	object_iterator = scene->objects;
	while (object_iterator != NULL)
	{
		if (object_iterator->type == OBJ_SPHERE)
			sphere_compute_constants((t_sphere*)&object_iterator->value);
		object_iterator = object_iterator->next;
	}
	handle_window_resizing(mlx, canvas, scene->camera, menu);
}
