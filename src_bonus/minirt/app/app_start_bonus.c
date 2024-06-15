/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_start_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:49:18 by tdubois           #+#    #+#             */
/*   Updated: 2024/06/15 22:29:13 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app_bonus.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/app_config_bonus.h"
#include "minirt/app/scene/scene_bonus.h"

static t_error	_app_init(
					t_app *app,
					t_scene *scene);
static void		_compute_constants(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas);

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
	app->scene = scene;
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(g_window_width, g_window_height, g_window_title, true);
	if (app->mlx == NULL)
		return (FAILURE);
	if (canvas_init(app->mlx, &app->canvas) == FAILURE
		|| menu_init(app->mlx, &app->menu, app->scene) == FAILURE
		|| mlx_loop_hook(app->mlx, app_loop, app) == false)
	{
		mlx_terminate(app->mlx);
		return (FAILURE);
	}
	_compute_constants(app->mlx, &app->menu, app->scene, &app->canvas);
	// scene->binary_tree = app->scene.binary_tree;
	return (SUCCESS);
}

static void	_compute_constants(
				mlx_t *mlx,
				t_menu *menu,
				t_scene *scene,
				t_canvas *canvas)
{
	t_object	*object_iterator;

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
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_TRIANGLE)
			triangle_compute_constants(
				&object_iterator->value.as_triangle,
				&object_iterator->bounding_box);
		else if (object_iterator->type == OBJ_OBJECT_FILE)
			object_file_compute_constants(
				&object_iterator->value.as_object_file,
				&object_iterator->bounding_box);
		object_iterator = object_iterator->next;
	}
	handle_window_resizing(mlx, menu, scene, canvas);
	scene->binary_tree = NULL;
	compute_scene_binary_tree(scene);
	compute_scene_planes(scene);
}
