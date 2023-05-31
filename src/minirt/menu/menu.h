/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:39:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 21:26:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

//> MENU MODEL

# include <stdint.h>
# include <minirt/scene/scene.h>
# include <minirt/utils/geometry.h>
# include <libft/libft.h>
# include <MLX42/MLX42.h>
# include <stdbool.h>

# define MENU_WIDTH 400 // width of menu in pixels
# define MENU_BACKGROUND_COLOR 0x333333FF

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

typedef struct s_menu
{
	bool			is_visible;

	mlx_image_t		*background;

	mlx_image_t		*camera_label_title;
	t_vec3_label	camera_pos_label;
	t_vec3_label	camera_dir_label;

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

//---- LIB --------------------------------------------------------------------#

/// float_label

void	float_label_update_position(
			t_menu *menu,
			t_float_label *label);
void	float_label_update_content(
			mlx_t *mlx,
			t_menu *menu,
			t_float_label *label);
void	float_label_show(
			t_float_label *label);
void	float_label_hide(
			t_float_label *label);

/// vec3_label

void	vec3_label_update_position(
			t_menu *menu,
			t_vec3_label *label);
void	vec3_label_update_content(
			mlx_t *mlx,
			t_menu *menu,
			t_vec3_label *label);
void	vec3_label_show(
			t_vec3_label *label);
void	vec3_label_hide(
			t_vec3_label *label);

#endif//MENU_H
