/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_panel_register.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:23:23 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "minirt/app/scene/scene.h"

static void	_register_position_label(
				t_menu *menu,
				t_object_file *objf);
static void	_register_x_axis_label(
				t_menu *menu,
				t_object_file *objf);
static void	_register_y_axis_label(
				t_menu *menu,
				t_object_file *objf);
static void	_register_size_label(
				t_menu *menu,
				t_object_file *objf);

void	object_file_panel_register(
			t_menu *menu,
			t_object_file *objf)
{
	menu->object_panel.object_type = OBJ_OBJECT_FILE;
	menu->object_panel.title = menu->object_panel.object_file_title;
	menu->object_panel.object_ptr = objf;
	_register_position_label(menu, objf);
	_register_x_axis_label(menu, objf);
	_register_y_axis_label(menu, objf);
	_register_size_label(menu, objf);
}

static void	_register_position_label(
				t_menu *menu,
				t_object_file *objf)
{
	t_object_file_panel *const	panel = &menu->object_panel.object_file_panel;

	panel->position_label.label_x.f = &objf->pos.x;
	panel->position_label.label_y.f = &objf->pos.y;
	panel->position_label.label_z.f = &objf->pos.z;
	panel->position_label_button_x.f = &objf->pos.x;
	panel->position_label_button_y.f = &objf->pos.y;
	panel->position_label_button_z.f = &objf->pos.z;
}

static void	_register_x_axis_label(
				t_menu *menu,
				t_object_file *objf)
{
	t_object_file_panel *const	panel = &menu->object_panel.object_file_panel;

	panel->x_axis_label.label_x.f = &objf->x_axis.x;
	panel->x_axis_label.label_y.f = &objf->x_axis.y;
	panel->x_axis_label.label_z.f = &objf->x_axis.z;
	panel->x_axis_label_button_x.f = &objf->x_axis.x;
	panel->x_axis_label_button_y.f = &objf->x_axis.y;
	panel->x_axis_label_button_z.f = &objf->x_axis.z;
}

static void	_register_y_axis_label(
				t_menu *menu,
				t_object_file *objf)
{
	t_object_file_panel *const	panel = &menu->object_panel.object_file_panel;

	panel->y_axis_label.label_x.f = &objf->y_axis.x;
	panel->y_axis_label.label_y.f = &objf->y_axis.y;
	panel->y_axis_label.label_z.f = &objf->y_axis.z;
	panel->y_axis_label_button_x.f = &objf->y_axis.x;
	panel->y_axis_label_button_y.f = &objf->y_axis.y;
	panel->y_axis_label_button_z.f = &objf->y_axis.z;
}

static void	_register_size_label(
				t_menu *menu,
				t_object_file *objf)
{
	t_object_file_panel *const	panel = &menu->object_panel.object_file_panel;

	panel->size_label.f = &objf->size;
	panel->size_label_button.f = &objf->size;
}
