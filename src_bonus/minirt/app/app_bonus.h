/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:28:10 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 16:33:56 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_BONUS_H
# define APP_BONUS_H

# include <stdbool.h>
# include <stdint.h>

# include "MLX42/MLX42.h"

# include "minirt/app/canvas/canvas_bonus.h"
# include "minirt/app/menu/menu_bonus.h"
# include "minirt/app/scene/scene_bonus.h"

//**** APP MODEL *************************************************************//

//> container for the context tpassed through app_loop

typedef struct s_app
{
	mlx_t		*mlx;
	t_menu		menu;
	t_scene		*scene;
	t_canvas	canvas;
}	t_app;

//---- INTERSECTION STRUCT ---------------------------------------------------//

typedef struct s_intersect_info
{
	float		distance;
	int			sub_part_id;
}	t_intersect_info;

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
void			handle_mouse_clicks(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene,
					t_canvas *canvas);

/// rendering core

void			render_canvas(
					t_app *app,
					bool should_render);
void			render_fast_on_front_canvas(
					t_app *app,
					int32_t ppr);
int32_t			render_next_pixels_til_tmax_on_back_canvas(
					t_app *app,
					int32_t pixel_rendered);
int32_t			render_ray_from_camera(
					t_scene const *scene,
					t_ray const *ray,
					bool show_spotlights);

t_ray			create_ray_from_pixel_coords(
					t_camera const *camera,
					t_canvas const *canvas,
					int32_t const coords[2]);

/// raytracing

typedef struct s_pixel_info
{
	t_ray	normal;
	t_vec2	pos;
}	t_pixel_info;

t_color			render_ray_on_object(
					t_scene const *scene,
					t_object const *intersected_object,
					t_ray const *ray,
					t_intersect_info const *intersect_info);
int32_t			render_ray(
					t_scene const *scene,
					t_object const *obj,
					t_ray const *ray,
					t_intersect_info const *intersect_info);

/// intersections

t_object		*fetch_closest_intersection(
					t_ray const *ray,
					t_object *objects,
					t_intersect_info *intersect_info);
t_object		*fetch_closest_intersection_in_tree(
					t_ray const *ray,
					t_scene_binary_part *tree,
					t_intersect_info *intersect_info);
t_light			*fetch_closer_spotlight(
					t_ray const *ray,
					t_light *lights,
					t_intersect_info *intersect_info);
bool			test_intersection_with_obj(
					t_ray const *ray,
					t_object const *object,
					t_intersect_info *intersect_info);

/// sphere intersections

bool			test_intersection_with_sphere(
					t_ray const *ray,
					t_sphere const *sphere,
					t_intersect_info *intersect_info);
bool			test_intersection_with_sphere_from_inside(
					t_ray const *ray,
					t_sphere const *sphere,
					t_intersect_info *intersect_info);

/// plane intersections

bool			test_intersection_with_plane(
					t_ray const *ray,
					t_plane const *plane,
					t_intersect_info *intersect_info);

/// cylinder intersections

bool			test_intersection_with_cylinder(
					t_ray const *ray,
					t_cylinder const *cylinder,
					t_intersect_info *intersect_info);
bool			test_intersection_with_cylinder_from_inside(
					t_ray const *ray,
					t_cylinder const *cylinder,
					t_intersect_info *intersect_info);

/// cone intersections

bool			test_intersection_with_cone(
					t_ray const *ray,
					t_cone const *cone,
					t_intersect_info *intersect_info);
bool			test_intersection_with_cone_from_inside(
					t_ray const *ray,
					t_cone const *cone,
					t_intersect_info *intersect_info);

/// cube intersections

bool			compute_intersection_distance(
					t_intersect_info *intersect_info,
					float abc[3]);
bool			compute_intersection_distance_from_inside(
					t_intersect_info *intersect_info,
					float abc[3]);
bool			test_intersection_with_cube(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_right(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_left(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_top(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_bot(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_front(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_with_back(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			test_intersection_with_cube_from_inside(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_right(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_left(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_top(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_bot(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_front(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);
bool			intersection_inside_with_back(
					t_ray const *ray,
					t_cube const *cube,
					t_intersect_info *intersect_info);

/// triangle intersections

bool			test_intersection_with_triangle(
					t_ray const *ray,
					t_triangle const *triangle,
					t_intersect_info *intersect_info);

/// bounding box intersections
bool			test_intersection_with_bounding_box(
					t_ray const *ray,
					t_bounding_box const *bbox);

/// object_file intersections

bool			test_intersection_with_object_file(
					t_ray const *ray,
					t_object_file const *objf,
					t_intersect_info *intersect_info);
bool			test_intersection_with_object_file_from_inside(
					t_ray const *ray,
					t_object_file const *objf,
					t_intersect_info *intersect_info);
bool			test_intersection_with_object_triangle(
					t_ray const *ray,
					t_object_triangle const *triangle,
					t_intersect_info *intersect_info);
bool			test_intersection_with_object_triangle_reverse(
					t_ray const *ray,
					t_object_triangle const *triangle,
					t_intersect_info *intersect_info);
bool			test_intersection_with_object_rectangle(
					t_ray const *ray,
					t_object_rectangle const *rectangle,
					t_intersect_info *intersect_info);
bool			test_intersection_with_object_rectangle_reverse(
					t_ray const *ray,
					t_object_rectangle const *rectangle,
					t_intersect_info *intersect_info);

t_color			intersect_loop_without_param_obj(
					t_object const *object,
					t_scene const *scene,
					t_ray const *ray);

/// normal rays

void			compute_normal_ray(
					t_object const *object,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_sphere(
					t_object const *sphere,
					t_ray const *ray,
					float distance,
					t_ray *normal);
void			compute_normal_ray_on_plane(
					t_object const *sphere,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_cylinder(
					t_object const *cylinder,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_cone(
					t_object const *cone,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_cube(
					t_object const *cube,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_triangle(
					t_object const *triangle,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);
void			compute_normal_ray_on_object_file(
					t_object const *object_file,
					t_ray const *ray,
					t_intersect_info const *intersect_info,
					t_ray *normal);

/// illumination

typedef struct s_phong_model
{
	t_ray const		*from_camera;
	t_ray const		*normal;
	t_light const	*spotlight;
}	t_phong_model;

t_color			check_dynamic_illumination(
					t_scene const *scene,
					t_object const *object,
					t_ray const *ray,
					t_ray const *normal);

t_color			compute_illumination(
					t_scene const *scene,
					t_object const *object,
					t_ray const *ray,
					t_ray const *normal);

// transparency

t_color			compute_refracted_color(
					t_object const *object,
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal);

// reflection

t_color			compute_reflected_color(
					t_object const *object,
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal);
t_color			reflection_outside_object(
					t_object const *object,
					t_scene const *scene,
					t_ray const *ray,
					t_ray const *normal);

// mapping

t_vec2			get_object_pixel_pos(
					t_object const *object,
					t_ray const *ray,
					t_ray const *normal,
					t_intersect_info const *intersect_info);
t_vec2			get_sphere_pixel_pos(
					t_sphere const *sphere,
					t_ray const *normal);
t_vec2			get_plane_pixel_pos(
					t_plane const *plane,
					t_ray const *normal);
t_vec2			get_cylinder_pixel_pos(
					t_cylinder const *cylinder,
					t_ray const *ray,
					t_ray const *normal,
					t_intersect_info const *intersect_info);
t_vec2			get_cone_pixel_pos(
					t_cone const *cone,
					t_ray const *ray,
					t_ray const *normal,
					t_intersect_info const *intersect_info);
t_vec2			get_cube_pixel_pos(
					t_cube const *cube,
					t_ray const *normal,
					t_intersect_info const *intersect_info);
t_vec2			get_triangle_pixel_pos(
					t_triangle const *triangle,
					t_ray const *normal);
t_vec2			get_object_file_pixel_pos(
					t_object_file const *objf,
					t_ray const *normal,
					t_intersect_info const *intersect_info);

t_color			get_base_color_object(
					t_object const *intersected_object,
					t_vec2 const *pixel_pos);

t_color			apply_texture(
					mlx_texture_t const *texture,
					t_vec2 const *pixel_pos);

void			compute_normal_map(
					t_object const *intersected_object,
					t_intersect_info const *intersect_info,
					t_vec2 const *pixel_pos,
					t_ray *normal);
void			compute_normal_base_sphere(
					t_vec3 normal_base[3]);
void			compute_normal_base_plane(
					t_vec3 normal_base[3]);
void			compute_normal_base_cylinder(
					t_vec3 normal_base[3],
					t_cylinder const *cylinder,
					t_intersect_info const *intersect_info);
void			compute_normal_base_cone(
					t_vec3 normal_base[3],
					t_cone const *cone,
					t_intersect_info const *intersect_info);
void			compute_normal_base_cube(
					t_vec3 normal_base[3],
					t_cube const *cube,
					t_intersect_info const *intersect_info);
void			compute_normal_base_triangle(
					t_vec3 normal_base[3]);
void			compute_normal_base_object_file(
					t_vec3 normal_base[3],
					t_object_file const *objf,
					t_intersect_info const *intersect_info);
void			apply_normal_map(
					mlx_texture_t const *normal_map,
					t_vec2 const *pixel_pos,
					t_ray *normal);
#endif//APP_BONUS_H
