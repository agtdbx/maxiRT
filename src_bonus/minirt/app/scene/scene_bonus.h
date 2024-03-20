/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:43:24 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/20 21:38:53 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "libft/libft.h"
# include "MLX42/MLX42.h"

# include "minirt/app/canvas/canvas_bonus.h"
# include "minirt/app/utils/color/color_bonus.h"
# include "minirt/app/utils/geometry/geometry_bonus.h"

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

//---- TRIANGLE --------------------------------------------------------------//

typedef struct s_triangle
{
	t_vec3	point1;
	t_vec3	point2;
	t_vec3	point3;

	t_vec3	normal;
	t_vec3	edge1; // point2 - point1
	t_vec3	edge2; // point3 - point1
	float	BCy; // point2.y - point3.y;
	float	CBx; // point3.x - point2.x;
	float	CAy; // point3.y - point1.y;
	float	ACx; // point1.x - point3.x;
	float	div_part; // div part for pixel pos
	int		pixel_pos_base;
}	t_triangle;

void			triangle_compute_constants(
					t_triangle *triangle);

//---- OBJECT FILE------------------------------------------------------------//

typedef enum e_object_polygon_t
{
	OBJF_TRIANGLE,
	OBJF_RECTANGLE
}	t_object_polygon_t;

typedef struct s_object_triangle
{
	int		vertice_1;
	int		vertice_2;
	int		vertice_3;

	t_vec3	point1;
	t_vec3	point2;
	t_vec3	point3;
	t_vec3	normal;
	t_vec3	edge1; // point1 to point2
	t_vec3	edge2; // point1 to point3
	float	BCy; // point2.y - point3.y;
	float	CBx; // point3.x - point2.x;
	float	CAy; // point3.y - point1.y;
	float	ACx; // point1.x - point3.x;
	float	div_part; // div part for pixel pos
	int		pixel_pos_base;
}	t_object_triangle;

typedef struct s_object_rectangle
{
	int		vertice_1;
	int		vertice_2;
	int		vertice_3;
	int		vertice_4;

	t_vec3	point1;
	t_vec3	point2;
	t_vec3	point3;
	t_vec3	point4;
	t_vec3	normal;
	t_vec3	x_axis; // for pixel pos
	t_vec3	y_axis; // for pixel pos
	float	inv_width;
	float	inv_height;
}	t_object_rectangle;

typedef union u_object_polygon_v
{
	t_object_triangle		as_objf_triangle;
	t_object_rectangle		as_objf_rectangle;
}	t_object_polygon_v;


typedef struct s_object_polygon
{
	t_object_polygon_t	type;
	t_object_polygon_v	value;
}	t_object_polygon;

// For binary tree
typedef struct s_object_face
{
	t_vec3	normal;

	t_vec3	point_ru;
	t_vec3	point_lu;
	t_vec3	point_rd;
	t_vec3	point_ld;

	float	inv_width;
	float	inv_height;

}	t_object_face;

typedef struct s_object_bounding_box
{
	float			min_x;
	float			min_y;
	float			min_z;
	float			max_x;
	float			max_y;
	float			max_z;

	t_object_face	front;
	t_object_face	back;
	t_object_face	left;
	t_object_face	right;
	t_object_face	up;
	t_object_face	down;

}	t_object_bounding_box;

typedef struct s_object_binary_polygon
{
	t_object_polygon				*polygon;

	int								polygon_id;

	struct s_object_binary_polygon	*next;

}	t_object_binary_polygon;

typedef struct s_object_binary_part
{
	struct s_object_binary_part	*child_1;
	struct s_object_binary_part	*child_2;

	t_object_bounding_box		bounding_box;
	t_object_binary_polygon		*polygons;

}	t_object_binary_part;

typedef struct s_object_file
{
	t_vec3					pos;
	t_vec3					x_axis;
	t_vec3					y_axis;
	t_vec3					*vertices;
	t_vec3					*real_vertices;
	t_object_polygon		*polygons;
	int						nb_vertices;
	int						nb_polygons;

	float					size;
	t_vec3					z_axis;
	t_cube					bounding_box;

	t_object_binary_part	*binary_partition;

}	t_object_file;

void			add_object_binary_polygons(
					t_object_binary_polygon **polygons,
					t_object_polygon *new_polygon,
					int polygon_id);
void			free_object_binary_polygons(
					t_object_binary_polygon *polygon);
void			create_new_object_binary_tree_part(
					t_object_binary_part **new);
void			free_object_binary_tree(
					t_object_binary_part *part);
void			compute_objf_triangle(
					t_object_file *objf,
					t_object_triangle *triangle);
void			compute_objf_rectangle(
					t_object_file *objf,
					t_object_rectangle *rectangle);
void			compute_objf_bounding_boxes(
					t_object_file *objf);
void			object_file_compute_constants(
					t_object_file *objf);

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
	OBJ_TRIANGLE,
	OBJ_OBJECT_FILE,
}	t_object_t;

typedef union u_object_v
{
	t_sphere		as_sphere;
	t_plane			as_plane;
	t_cylinder		as_cylinder;
	t_cone			as_cone;
	t_cube			as_cube;
	t_triangle		as_triangle;
	t_object_file	as_object_file;
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

#endif //SCENE_BONUS_H
