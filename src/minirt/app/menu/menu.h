/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:39:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:59:32 by tdubois          ###   ########.fr       */
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
	bool		is_visible;

	int32_t		x;
	int32_t		y;
	char const	*prefix;
	float const	*f;

	mlx_image_t	*img;
}	t_float_label;

typedef struct s_vec3_label
{
	bool			is_visible;

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
	bool		is_visible;

	int32_t		x;
	int32_t		y;
	char const	*title;

	mlx_image_t	*img_title;
	t_int_label	label_r;
	t_int_label	label_g;
	t_int_label	label_b;
}	t_color_label;

typedef struct s_menu
{
	bool			is_visible;

	mlx_image_t		*background;

	mlx_image_t		*camera_label_title;
	t_vec3_label	camera_pos_label;
	t_vec3_label	camera_dir_label;

	mlx_image_t		*ambient_label_title;
	t_color_label	ambient_color_label;
	t_float_label	ambient_ratio_label;

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
void	menu_draw(
			mlx_t *mlx,
			t_menu *menu);

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
void	camera_label_draw(
			mlx_t *mlx,
			t_menu *menu);

/// ambient_label

void	ambient_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene);
void	ambient_label_show(
			t_menu *menu);
void	ambient_label_hide(
			t_menu *menu);
void	ambient_label_draw(
			mlx_t *mlx,
			t_menu *menu);

//---- LIB --------------------------------------------------------------------#

/// float_label

void	float_label_show(
			t_float_label *label);
void	float_label_hide(
			t_float_label *label);
void	float_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_float_label *label);

/// vec3_label

void	vec3_label_show(
			t_vec3_label *label);
void	vec3_label_hide(
			t_vec3_label *label);
void	vec3_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_vec3_label *label);

/// int_label

void	int_label_show(
			t_int_label *label);
void	int_label_hide(
			t_int_label *label);
void	int_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_int_label *label);

/// color_label

void	color_label_show(
			t_color_label *label);
void	color_label_hide(
			t_color_label *label);
void	color_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_color_label *label);

#endif//MENU_H
