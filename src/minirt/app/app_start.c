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

#define FRONT_CANVAS 0
#define BACK_CANVAS 1

static t_error	_app_init(
					t_app *app,
					t_scene *scene);
static t_error	_init_render(t_app *app);
static void		_compute_constants(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas,
					t_render *render);
static t_error	_init_mutex_cond_sem(t_render *render);
static void		_app_end(t_app *app);

t_error	app_start(
			t_scene *scene)
{
	t_app	app;

	errno = 0;
	mlx_errno = 0;
	if (_app_init(&app, scene) == SUCCESS)
	{
		render_canvas(&app, true);
		mlx_loop(app.mlx);
		mlx_terminate(app.mlx);
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
	pthread_mutex_lock(&app->render.sync.queue_mut);
	del_queue(&app->render.queue);
	pthread_mutex_unlock(&app->render.sync.queue_mut);
	join_all_threads(app->render.workers);
	del_mut_cond_sem(&app->render.sync);
	free_encoder_context(&app->encoder);
	free(app->render.workers);
}

static t_error	_app_init(
					t_app *app,
					t_scene *scene)
{
	create_records_dir();
	app->scene = scene;
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(g_window_width, g_window_height, g_window_title, true);
	if (app->mlx == NULL)
		return (FAILURE);
	srand(time(NULL));
	_init_render(app);
	if (canvas_init(app->mlx, &app->canvas) == FAILURE
		|| init_encoder(&app->encoder, app->canvas.render_icon) == FAILURE
		|| menu_init(app->mlx, &app->menu, app->scene) == FAILURE
		|| threads_init(app) == FAILURE
		|| mlx_loop_hook(app->mlx, app_loop, app) == false)
	{
		mlx_terminate(app->mlx);
		return (FAILURE);
	}
	_compute_constants(app->mlx, &app->menu, app->scene, &app->canvas,
		&app->render);
	return (SUCCESS);
}

static t_error	_init_render(t_app *app)
{
	long	nb_threads;

	nb_threads = get_nb_threads();
	app->render.workers = malloc((nb_threads - 1) * sizeof(t_worker));
	if (app->render.workers == NULL)
	{
		free(app->render.queue);
		return FAILURE;
	}
	if (_init_mutex_cond_sem(&app->render) == FAILURE)
	{
		free(app->render.queue);
		free(app->render.workers);
		return FAILURE;
	}
	app->render.queue = NULL;
	app->render.sync = (t_sync){
		.nb_active_threads = 0,
		.nb_tasks_remain = 0,
		.pixel_rendered = 0,
		.keep_alive = 1,
	};
	app->render.canvas = &app->canvas;
	app->render.scene = app->scene;
	app->render.menu = &app->menu;
	return SUCCESS;
}

static void	_compute_constants(
				mlx_t *mlx,
				t_menu *menu,
				t_scene *scene,
				t_canvas *canvas,
				t_render *render)
{
	t_object	*object_iterator;
	int			nb_objects = 0;

	object_iterator = scene->objects;
	while (object_iterator != NULL)
	{
		if (object_iterator->type == OBJ_SPHERE)
			sphere_compute_constants(
			&object_iterator->value.as_sphere,
			&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_PLANE)
			plane_compute_constants(
				&object_iterator->value.as_plane,
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_CYLINDER)
			cylinder_compute_constants(
				&object_iterator->value.as_cylinder,
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_CONE)
			cone_compute_constants(
				&object_iterator->value.as_cone,
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_CUBE)
			cube_compute_constants(
				&object_iterator->value.as_cube,
				&object_iterator->bounding_box,
				0);
		else if (object_iterator->type == OBJ_TRIANGLE)
			triangle_compute_constants(
				&object_iterator->value.as_triangle,
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_OBJECT_FILE)
			object_file_compute_constants(
				&object_iterator->value.as_object_file,
				&object_iterator->bounding_box);
		object_iterator = object_iterator->next;
		nb_objects++;
	}
	handle_window_resizing(mlx, menu, scene, canvas, &render->sync);
	scene->binary_tree = NULL;
	compute_scene_binary_tree(scene);
	compute_scene_planes(scene);
	if (scene->skybox)
		cube_compute_constants(&scene->skybox->value.as_skybox.cube,
			NULL, 1);
}

static t_error	_init_mutex_cond_sem(t_render *render)
{
	if (pthread_mutex_init(&render->sync.queue_mut, NULL) != 0 ||
		pthread_mutex_init(&render->sync.canvas_mut[FRONT_CANVAS], NULL) != 0 ||
		pthread_mutex_init(&render->sync.canvas_mut[BACK_CANVAS], NULL) != 0 ||
		pthread_mutex_init(&render->sync.active_threads_mut, NULL) != 0)
	{
		perror("pthread_mutex_init() error");
		return FAILURE;
	}
	if (pthread_rwlock_init(&render->sync.scene_mut, NULL))
	{
		perror("pthread_rwlock_init() error");
		return FAILURE;
	}
	if (pthread_cond_init(&render->sync.finish_jobs_cond, NULL) != 0)
	{
		perror("pthread_cond_init() error");
		return FAILURE;
	}
	if (sem_init(&render->sync.jobs_sem, 0, 0) != 0)
	{
		perror("sem_init() error");
		return FAILURE;
	}
	return SUCCESS;
}
