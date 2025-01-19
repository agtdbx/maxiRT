/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:49:18 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/15 22:29:13 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/app_config.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/encode/encode.h"
#include "minirt/app/render/multithread/multithread.h"

#define FRONT_CANVAS 0
#define BACK_CANVAS 1
#define MIN_WIDTH 100
#define MIN_HEIGHT 100

static t_error	_app_init(
					t_app *app,
					t_scene *scene);
static void		_compute_constants(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas,
					t_render *render);
static void		_app_end(t_app *app);

t_error	app_start(
			t_scene *scene)
{
	t_app	app;

	errno = 0;
	mlx_errno = 0;
	if (_app_init(&app, scene) == SUCCESS)
	{
		mlx_set_window_limit(
			app.mlx,
			MIN_WIDTH,
			MIN_HEIGHT,
			g_window_width,
			g_window_height);
		mlx_loop(app.mlx);
		_app_end(&app);
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

static void _app_end(t_app *app)
{
	app->render.sync.keep_alive = 0;
	join_all_threads(app->render.workers);
	mlx_terminate(app->mlx);
	del_queue(&app->render.queue);
	del_mut_cond_sem(&app->render.sync);
	if (app->encoder.c)
		free_encoder_context(&app->encoder);
	free(app->render.workers);
}

static t_error	_app_init(
					t_app *app,
					t_scene *scene)
{
	app->scene = scene;
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(g_window_width, g_window_height, WINDOW_TITLE, true);
	if (app->mlx == NULL)
		return (FAILURE);
	if (canvas_init(app->mlx, &app->canvas) == FAILURE
		|| init_encoder(&app->encoder, app->mlx->width, app->mlx->height) == FAILURE
		|| menu_init(app->mlx, &app->menu, app->scene) == FAILURE
		|| init_multithread(&app->render, &app->canvas, app->scene, &app->menu) == FAILURE
		|| fill_and_start_threads(&app->render) == FAILURE
		|| mlx_loop_hook(app->mlx, app_loop, app) == false)
	{
		mlx_terminate(app->mlx);
		return (FAILURE);
	}
	_compute_constants(app->mlx, &app->menu, app->scene, &app->canvas,
		&app->render);
	scene->color_filter = (t_vec3){1.0f, 1.0f, 1.0f};
	return (SUCCESS);
}

static void	_compute_constants(
				mlx_t *mlx,
				t_menu *menu,
				t_scene *scene,
				t_canvas *canvas,
				t_render *render)
{
	t_object	*object_iterator;
	t_light		*light;

	object_iterator = scene->objects;
	while (object_iterator != NULL)
	{
		if (object_iterator->type == OBJ_SPHERE)
			sphere_compute_constants(
			&object_iterator->value.as_sphere);
		else if (object_iterator->type == OBJ_PLANE)
			plane_compute_constants(
				&object_iterator->value.as_plane);
		else if (object_iterator->type == OBJ_CYLINDER)
			cylinder_compute_constants(
				&object_iterator->value.as_cylinder);
		else if (object_iterator->type == OBJ_CONE)
			cone_compute_constants(
				&object_iterator->value.as_cone);
		else if (object_iterator->type == OBJ_CUBE)
			cube_compute_constants(
				&object_iterator->value.as_cube,
				0);
		else if (object_iterator->type == OBJ_TRIANGLE)
			triangle_compute_constants(
				&object_iterator->value.as_triangle);
		else if (object_iterator->type == OBJ_OBJECT_FILE)
			object_file_compute_constants(
				&object_iterator->value.as_object_file);
		else if (object_iterator->type == OBJ_PARABOLOID)
			paraboloid_compute_constants(
				&object_iterator->value.as_paraboloid);
		object_iterator = object_iterator->next;
	}
	handle_window_resizing(mlx, menu, scene, canvas, &render->sync);
	if (scene->skybox)
		cube_compute_constants(&scene->skybox->value.as_skybox.cube, 1);

	light = scene->spotlights;
	while (light)
	{
		light_compute_constants(light);
		light = light->next;
	}
}

