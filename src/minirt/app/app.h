/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:25:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 13:37:08 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <minirt/menu/menu.h>
# include <minirt/scene/scene.h>
# include <minirt/canvas/canvas.h>

# include <MLX42/MLX42.h>

//****************************************************************************//
//**** WINDOW CONFIGURATION CONSTANTS ****************************************//

# define WINDOW_TITLE "maxiRT"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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

t_error		app_start(
				t_scene *scene);
void		app_loop(
				void *const data);

bool		update_camera_position(
				mlx_t *mlx,
				t_camera *camera);
bool		update_camera_direction(
				mlx_t *mlx,
				t_camera *camera);

void		render(
				t_app *app,
				bool should_render);

#endif//APP_H
