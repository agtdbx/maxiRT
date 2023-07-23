/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:43:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 12:44:31 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft/libft.h"
# include "MLX42/MLX42.h"

# include "minirt/app/canvas/canvas.h"
# include "minirt/app/utils/color/color.h"
# include "minirt/app/utils/geometry/geometry.h"

//---- SPHERE ----------------------------------------------------------------//

typedef struct s_sphere
{
	t_vec3	pos;
	float	diameter;

	float	radius;
	float	radius2;

}	t_sphere;

void			sphere_compute_constants(
					t_sphere *sphere);

//---- PLANE -----------------------------------------------------------------//

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;

	t_vec3	rev_normal;
}	t_plane;

void			plane_compute_constants(
					t_plane *plane);

//---- CYLINDER --------------------------------------------------------------//

typedef struct s_cylinder
{
	t_vec3	pos;
	float	diameter;
	float	height;
	t_vec3	axis;

	t_plane	bot;
	t_plane	top;
	float	radius;
	float	radius2;
	float	half_height;

}	t_cylinder;

void			cylinder_compute_constants(
					t_cylinder *cylinder);

//---- CONE ------------------------------------------------------------------//

typedef struct s_cone
{
	t_vec3	pos;
	float	diameter;
	float	height;
	t_vec3	axis;

	t_plane	end;
	float	radius;
	float	radius2;
	float	ratio;
}	t_cone;

void			cone_compute_constants(
					t_cone *cone);

//---- CUBE ------------------------------------------------------------------//

typedef struct s_cube
{
	t_vec3	pos;
	float	witdh;
	float	height;
	float	depth;
	t_vec3	x_axis;
	t_vec3	y_axis;

	t_vec3	z_axis;
	t_plane	front;
	t_plane	back;
	t_plane	top;
	t_plane	bot;
	t_plane	left;
	t_plane	right;
	float	half_witdh;
	float	half_height;
	float	half_depth;

}	t_cube;

void			cube_compute_constants(
					t_cube *cube);
void			cube_compute_constants_from_menu(
					t_cube *cube);

//---- COLOR INTERFACE -------------------------------------------------------//

typedef enum e_color_t
{
	C_COLOR,
	C_CHECKBOARD,
	C_TEXTURE,
}	t_color_t;

//---- OBJECT INTERFACE ------------------------------------------------------//

typedef enum e_object_t
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_CUBE,
}	t_object_t;

typedef union u_object_v
{
	t_sphere	as_sphere;
	t_plane		as_plane;
	t_cylinder	as_cylinder;
	t_cone		as_cone;
	t_cube		as_cube;
}	t_object_v;

typedef struct s_object
{
	t_object_t		type;
	t_object_v		value;

	t_color_t		color_type;
	t_color			color;
	mlx_texture_t	*texture;
	mlx_texture_t	*normal_map;

	float			opacity;
	float			density;
	float			reflection;

	struct s_object	*next;
}	t_object;

//---- LIGHT -----------------------------------------------------------------//

typedef struct s_light
{
	t_vec3			pos;
	t_color			color;
	float			brightness;

	struct s_light	*next;
}	t_light;

//---- CAMERA ----------------------------------------------------------------//

typedef struct s_camera
{
	float	fov;
	t_vec3	pos;
	t_vec3	direction;

	t_vec3	o_x;
	t_vec3	o_y;
	t_vec3	move_forward;
	float	focal;
}	t_camera;

void			camera_compute_constants(
					t_canvas const *canvas,
					t_camera *camera);

//---- SCENE -----------------------------------------------------------------//

typedef struct s_scene
{
	t_object	*objects;
	t_light		*spotlights;
	t_light		*ambient_lightning;
	t_camera	*camera;
}	t_scene;

t_error			scene_add_object(
					t_scene *scene,
					t_object *obj);

void			scene_del(
					t_scene *scene);

#endif//SCENE_H
