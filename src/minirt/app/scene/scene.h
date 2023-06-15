/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:03:21 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/15 18:19:12 by aderouba         ###   ########.fr       */
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

void	sphere_compute_constants(
			t_sphere *sphere);

//---- PLANE -----------------------------------------------------------------//

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;

	t_vec3	rev_normal;

}	t_plane;

//---- CYLINDER --------------------------------------------------------------//

typedef struct s_cylinder
{
	t_vec3	pos;
	float	radius;
	float	height;
	t_vec3	axis;

	t_plane	bot;
	t_plane	top;
	float	radius2;

}	t_cylinder;

//---- OBJECT INTERFACE ------------------------------------------------------//

typedef enum e_object_t
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}	t_object_t;

typedef union u_object_v
{
	t_sphere	as_sphere;
	t_plane		as_plane;
	t_cylinder	as_cylinder;
}	t_object_v;

typedef struct s_object
{
	t_object_t		type;
	t_object_v		value;

	t_color			color;

	float			opacity;
	float			reflection;
	float			refraction;
	float			density;

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
	float	focal;
}	t_camera;

void		camera_compute_constants(
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

t_error		scene_add_object(
				t_scene *scene,
				t_object *obj);

void		scene_del(
				t_scene *scene);

#endif//SCENE_H
