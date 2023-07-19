/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:39:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 17:36:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include <stdbool.h>
# include <stdint.h>

# include "MLX42/MLX42.h"
# include "libft/libft.h"

# include "minirt/app/scene/scene.h"
# include "minirt/app/utils/geometry/geometry.h"

typedef struct s_float_label
{
	int32_t		x;
	int32_t		y;
	char const	*prefix;
	float const	*f;

	mlx_image_t	*img;
}	t_float_label;

typedef struct s_vec3_label
{
	int32_t			x;
	int32_t			y;
	char const		*title;

	mlx_image_t		*img_title;
	t_float_label	label_x;
	t_float_label	label_y;
	t_float_label	label_z;
}	t_vec3_label;

typedef t_float_label	t_int_label;

typedef struct s_color_label
{
	int32_t		x;
	int32_t		y;
	char const	*title;

	mlx_image_t	*img_title;
	t_int_label	label_r;
	t_int_label	label_g;
	t_int_label	label_b;
}	t_color_label;

typedef struct s_button
{
	int32_t		x;
	int32_t		y;

	mlx_image_t	*img;
	mlx_image_t	*img_minus;
	mlx_image_t	*img_plus;
	int32_t		size;

	float		*f;
	float		max;
	float		min;
	float		step;
}	t_button;

typedef struct s_sphere_panel
{
	t_vec3_label	position_label;
	t_button		position_label_button_x;
	t_button		position_label_button_y;
	t_button		position_label_button_z;

	t_float_label	diameter_label;
	t_button		diameter_label_button;
}	t_sphere_panel;

typedef struct s_plane_panel
{
	t_vec3_label	position_label;
	t_button		position_label_button_x;
	t_button		position_label_button_y;
	t_button		position_label_button_z;

	t_vec3_label	direction_label;
	t_button		direction_label_button_x;
	t_button		direction_label_button_y;
	t_button		direction_label_button_z;
}	t_plane_panel;

typedef struct s_cylinder_panel
{
	t_vec3_label	position_label;
	t_button		position_label_button_x;
	t_button		position_label_button_y;
	t_button		position_label_button_z;

	t_vec3_label	direction_label;
	t_button		direction_label_button_x;
	t_button		direction_label_button_y;
	t_button		direction_label_button_z;

	t_float_label	diameter_label;
	t_button		diameter_label_button;

	t_float_label	height_label;
	t_button		height_label_button;
}	t_cylinder_panel;

typedef struct s_object_panel
{
	bool				is_enabled;
	t_object_t			object_type;
	void				*object_ptr;

	mlx_image_t			*title;
	mlx_image_t			*plane_title;
	mlx_image_t			*sphere_title;
	mlx_image_t			*cylinder_title;

	t_color_label		color_label;
	t_button			color_label_button_r;
	t_button			color_label_button_g;
	t_button			color_label_button_b;

	t_float_label		opacity_label;
	t_button			opacity_label_button;

	t_float_label		density_label;
	t_button			density_label_button;

	t_float_label		reflection_label;
	t_button			reflection_label_button;

	t_plane_panel		plane_panel;
	t_sphere_panel		sphere_label;
	t_cylinder_panel	cylinder_panel;

}	t_object_panel;

typedef struct s_light_panel
{
	bool			is_enabled;
	void			*light_ptr;

	mlx_image_t		*title;

	t_color_label	color_label;
	t_button		color_label_button_r;
	t_button		color_label_button_g;
	t_button		color_label_button_b;

	t_float_label	intensity_label;
	t_button		intensity_label_button;

	t_vec3_label	position_label;
	t_button		position_label_button_x;
	t_button		position_label_button_y;
	t_button		position_label_button_z;

}	t_light_panel;

typedef struct s_menu
{
	bool			is_visible;

	mlx_image_t		*background;

	mlx_image_t		*camera_label_title;
	t_vec3_label	camera_pos_label;
	t_vec3_label	camera_dir_label;
	t_float_label	camera_fov_label;
	t_button		camera_fov_button;

	mlx_image_t		*ambient_label_title;
	t_color_label	ambient_color_label;
	t_button		ambient_color_button_r;
	t_button		ambient_color_button_g;
	t_button		ambient_color_button_b;
	t_float_label	ambient_ratio_label;
	t_button		ambient_ratio_button;

	t_light_panel	light_panel;
	t_object_panel	object_panel;
}	t_menu;

t_error	menu_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene);
void	menu_update_position(
			mlx_t const *mlx,
			t_menu *menu);
void	menu_show(
			t_menu *menu);
void	menu_hide(
			t_menu *menu);
bool	menu_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_canvas *canvas,
			t_scene const *scene);

//---- COMPONENTS -------------------------------------------------------------#

/// background

void	background_draw(
			t_menu *menu);

/// camera_label

void	camera_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene);
void	camera_label_show(
			t_menu *menu);
void	camera_label_hide(
			t_menu *menu);
bool	camera_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_canvas *canvas,
			t_scene const *scene);

/// ambient_label

void	ambient_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene);
void	ambient_label_show(
			t_menu *menu);
void	ambient_label_hide(
			t_menu *menu);
bool	ambient_label_draw(
			mlx_t *mlx,
			t_menu *menu);

/// light_panel

void	light_panel_init(
			mlx_t *mlx,
			t_menu *menu);
void	light_panel_show(
			t_menu *menu);
void	light_panel_hide(
			t_menu *menu);
bool	light_panel_draw(
			mlx_t *mlx,
			t_menu *menu);
void	light_panel_register(
			t_menu *menu,
			t_light *light);

/// object_panel

void	object_panel_init(
			mlx_t *mlx,
			t_menu *menu);
void	object_panel_show(
			t_menu *menu);
void	object_panel_hide(
			t_menu *menu);
bool	object_panel_draw(
			mlx_t *mlx,
			t_menu *menu);
void	object_panel_register(
			t_menu *menu,
			t_object *object);

/// sphere_panel

void	sphere_panel_init(
			mlx_t *mlx,
			t_menu *menu);
void	sphere_panel_show(
			t_menu *menu);
void	sphere_panel_hide(
			t_menu *menu);
bool	sphere_panel_draw(
			mlx_t *mlx,
			t_menu *menu);
void	sphere_panel_register(
			t_menu *menu,
			t_sphere *sphere);

/// plane_panel

void	plane_panel_init(
			mlx_t *mlx,
			t_menu *menu);
void	plane_panel_show(
			t_menu *menu);
void	plane_panel_hide(
			t_menu *menu);
bool	plane_panel_draw(
			mlx_t *mlx,
			t_menu *menu);
void	plane_panel_register(
			t_menu *menu,
			t_plane *plane);

/// cylinder_panel

void	cylinder_panel_init(
			mlx_t *mlx,
			t_menu *menu);
void	cylinder_panel_show(
			t_menu *menu);
void	cylinder_panel_hide(
			t_menu *menu);
bool	cylinder_panel_draw(
			mlx_t *mlx,
			t_menu *menu);
void	cylinder_panel_register(
			t_menu *menu,
			t_cylinder *cylinder);

//---- LIB --------------------------------------------------------------------#

/// float buttons

void	button_init(
			mlx_t *mlx,
			t_button *button,
			int32_t	pos[2]);
void	button_show(
			t_button *button);
void	button_hide(
			t_button *button);
bool	button_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_button *button);

/// float_label

void	float_label_init(
			t_float_label *label,
			char const *str,
			uint32_t pos[2]);
void	float_label_show(
			t_float_label *label);
void	float_label_hide(
			t_float_label *label);
void	float_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_float_label *label);

/// vec3_label

t_vec3_label	vec3_label_init(
					mlx_t *mlx,
					t_menu *menu,
					char const *title,
					uint32_t const pos[2]);
void	vec3_label_show(
			t_vec3_label *label);
void	vec3_label_hide(
			t_vec3_label *label);
void	vec3_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_vec3_label *label);

/// int_label

void	int_label_init(
			t_int_label *label,
			char const *prefix,
			uint32_t const pos[2]);
void	int_label_show(
			t_int_label *label);
void	int_label_hide(
			t_int_label *label);
void	int_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_int_label *label);

/// color_label

void	color_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_color_label *label,
			uint32_t const pos[2]);
void	color_label_show(
			t_color_label *label);
void	color_label_hide(
			t_color_label *label);
void	color_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_color_label *label);

#endif//MENU_H
