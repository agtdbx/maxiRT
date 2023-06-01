/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:25:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/01 13:58:00 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <minirt/menu/menu.h>
# include <minirt/scene/scene.h>
# include <minirt/canvas/canvas.h>

# include <MLX42/MLX42.h>
# include <stdbool.h>

//****************************************************************************//
//**** WINDOW CONFIGURATION CONSTANTS ****************************************//

# define WINDOW_TITLE "maxiRT"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 995

//TODO(tdubois)
// # define WINDOW_WIDTH 240
// # define WINDOW_HEIGHT 180

//****************************************************************************//
//**** RENDERING CONFIGURATION CONSTANTS *************************************//

// cap game loop at 64 or 32 ticks per second
// # define MAX_TPS_64 0.017
// # define MAX_TPS_32 0.032
// # define MAX_TPS_16 0.063
// # define MINIMUM_RENDERING_TIMESTEP_IN_SECONDS MAX_TPS_16

//****************************************************************************//
//**** APP MODEL *************************************************************//

//> container for the context tpassed through app_loop

typedef struct s_app
{
	mlx_t		*mlx;
	t_menu		menu;
	t_scene		scene;
	t_canvas	canvas;
}	t_app;

//****************************************************************************//
//**** METHODS ***************************************************************//

t_error			app_start(
					t_scene *scene);
void			app_loop(
					void *const data);

bool			handle_window_resizing(
					mlx_t const *mlx,
					t_canvas *canvas,
					t_camera *camera,
					t_menu *menu);
bool			handle_translations(
					mlx_t *mlx,
					t_camera *camera);
bool			handle_rotations(
					mlx_t *mlx,
					t_canvas const *canvas,
					t_camera *camera);
bool			handle_menu_toggling(
					mlx_t *mlx,
					t_menu *menu);

void			render_canvas(
					t_app *app,
					bool should_render);
int32_t			render_ray_from_camera(
					t_scene const *scene,
					t_ray const *ray,
					bool show_spotlights);

int32_t			render_ray_on_object(
					t_scene const *scene,
					t_object const *intersected_object,
					t_ray const *ray,
					float distance);
int32_t			render_ray_on_sphere(
					t_scene const *scene,
					t_sphere const *sphere,
					t_ray const *ray,
					float distance);

t_object const	*fetch_closest_intersection(
					t_ray const *ray,
					t_object const *objects,
					float *distance);
bool			test_intersection_with_sphere(
					t_ray const *ray,
					t_sphere const *sphere,
					float *distance);

#endif//APP_H
