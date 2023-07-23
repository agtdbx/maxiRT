/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_panel_register.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 13:05:06 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/scene/scene_bonus.h"

static void	_register_position_label(
				t_menu *menu,
				t_cube *cube);
static void	_register_x_axis_label(
				t_menu *menu,
				t_cube *cube);
static void	_register_y_axis_label(
				t_menu *menu,
				t_cube *cube);
static void	_register_size_labels(
				t_menu *menu,
				t_cube *cube);

void	cube_panel_register(
			t_menu *menu,
			t_cube *cube)
{
	menu->object_panel.object_type = OBJ_CUBE;
	menu->object_panel.title = menu->object_panel.cube_title;
	menu->object_panel.object_ptr = cube;
	_register_position_label(menu, cube);
	_register_x_axis_label(menu, cube);
	_register_y_axis_label(menu, cube);
	_register_size_labels(menu, cube);
}

static void	_register_position_label(
				t_menu *menu,
				t_cube *cube)
{
	t_cube_panel *const	panel = &menu->object_panel.cube_panel;

	panel->position_label.label_x.f = &cube->pos.x;
	panel->position_label.label_y.f = &cube->pos.y;
	panel->position_label.label_z.f = &cube->pos.z;
	panel->position_label_button_x.f = &cube->pos.x;
	panel->position_label_button_y.f = &cube->pos.y;
	panel->position_label_button_z.f = &cube->pos.z;
}

static void	_register_x_axis_label(
				t_menu *menu,
				t_cube *cube)
{
	t_cube_panel *const	panel = &menu->object_panel.cube_panel;

	panel->x_axis_label.label_x.f = &cube->x_axis.x;
	panel->x_axis_label.label_y.f = &cube->x_axis.y;
	panel->x_axis_label.label_z.f = &cube->x_axis.z;
	panel->x_axis_label_button_x.f = &cube->x_axis.x;
	panel->x_axis_label_button_y.f = &cube->x_axis.y;
	panel->x_axis_label_button_z.f = &cube->x_axis.z;
}

static void	_register_y_axis_label(
				t_menu *menu,
				t_cube *cube)
{
	t_cube_panel *const	panel = &menu->object_panel.cube_panel;

	panel->y_axis_label.label_x.f = &cube->y_axis.x;
	panel->y_axis_label.label_y.f = &cube->y_axis.y;
	panel->y_axis_label.label_z.f = &cube->y_axis.z;
	panel->y_axis_label_button_x.f = &cube->y_axis.x;
	panel->y_axis_label_button_y.f = &cube->y_axis.y;
	panel->y_axis_label_button_z.f = &cube->y_axis.z;
}

static void	_register_size_labels(
				t_menu *menu,
				t_cube *cube)
{
	t_cube_panel *const	panel = &menu->object_panel.cube_panel;

	panel->width_label.f = &cube->witdh;
	panel->width_label_button.f = &cube->witdh;
	panel->height_label.f = &cube->height;
	panel->height_label_button.f = &cube->height;
	panel->depth_label.f = &cube->depth;
	panel->depth_label_button.f = &cube->depth;
}
