/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:25:17 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/19 12:17:32 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <stdbool.h>
# include <stdint.h>

# include "MLX42/MLX42.h"

# include "minirt/app/canvas/canvas.h"
# include "minirt/app/menu/menu.h"
# include "minirt/app/scene/scene.h"

//**** APP MODEL *************************************************************//

//> container for the context tpassed through app_loop

typedef struct s_app
{
	mlx_t		*mlx;
	t_menu		menu;
	t_scene		scene;
	t_canvas	canvas;
}	t_app;

//**** METHODS ***************************************************************//

/// core

t_error			app_start(
					t_scene *scene);
void			app_loop(
					void *const data);

/// inputs handlers

bool			handle_window_resizing(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas);
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
bool			handle_mouse_clicks(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas);

/// rendering core

void			render_canvas(
					t_app *app,
					bool should_render);
void			render_one_pixel(
					t_scene const *scene,
					t_canvas const *canvas,
					int32_t pixel_index,
					bool show_spotlights);
int32_t			render_ray_from_camera(
					t_scene const *scene,
					t_ray const *ray,
					bool show_spotlights);

/// raytracing

t_color			render_ray_on_object(
					t_scene const *scene,
					t_object const *intersected_object,
					t_ray const *ray,
					float distance);
int32_t			render_ray(
					t_scene const *scene,
					t_object const *obj,
					t_ray const *ray,
					float distance);

/// intersections

t_object const	*fetch_closest_intersection(
					t_ray const *ray,
					t_object const *objects,
					float *distance);
bool			test_intersection_with_obj(
					t_ray const *ray,
					t_object const *object,
					float *distance);
bool			test_intersection_with_sphere(
					t_ray const *ray,
					t_sphere const *sphere,
					float *distance);
bool			test_intersection_with_sphere_from_inside(
					t_ray const *ray,
					t_sphere const *sphere,
					float *distance);

/// normal rays

void			compute_normal_ray(
					t_object const *object,
					t_ray const *ray,
					float distance,
					t_ray *normal);

/// illumination

typedef struct s_phong_model
{
	t_ray const		*from_camera;
	t_ray const		*normal;
	t_light const	*spotlight;
}	t_phong_model;

void			compute_illumination(
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal,
					t_color *illumination);


// transparency

t_color			compute_refracted_color(
					t_object const *object,
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal);

#endif//APP_H
