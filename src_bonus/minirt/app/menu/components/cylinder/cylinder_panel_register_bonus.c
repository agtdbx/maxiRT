/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_panel_register_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:24:08 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/scene/scene_bonus.h"

static void	_register_position_and_direction_labels(
				t_menu *menu,
				t_cylinder *cylinder);
static void	_register_diameter_and_height_labels(
				t_menu *menu,
				t_cylinder *cylinder);

void	cylinder_panel_register(
			t_menu *menu,
			t_cylinder *cylinder)
{
	menu->object_panel.object_type = OBJ_CYLINDER;
	menu->object_panel.title = menu->object_panel.cylinder_title;
	menu->object_panel.object_ptr = cylinder;
	_register_diameter_and_height_labels(menu, cylinder);
	_register_position_and_direction_labels(menu, cylinder);
}

static void	_register_position_and_direction_labels(
				t_menu *menu,
				t_cylinder *cylinder)
{
	t_cylinder_panel *const	panel = &menu->object_panel.cylinder_panel;

	panel->position_label.label_x.f = &cylinder->pos.x;
	panel->position_label.label_y.f = &cylinder->pos.y;
	panel->position_label.label_z.f = &cylinder->pos.z;
	panel->position_label_button_x.f = &cylinder->pos.x;
	panel->position_label_button_y.f = &cylinder->pos.y;
	panel->position_label_button_z.f = &cylinder->pos.z;
	panel->direction_label.label_x.f = &cylinder->axis.x;
	panel->direction_label.label_y.f = &cylinder->axis.y;
	panel->direction_label.label_z.f = &cylinder->axis.z;
	panel->direction_label_button_x.f = &cylinder->axis.x;
	panel->direction_label_button_y.f = &cylinder->axis.y;
	panel->direction_label_button_z.f = &cylinder->axis.z;
}

static void	_register_diameter_and_height_labels(
				t_menu *menu,
				t_cylinder *cylinder)
{
	t_cylinder_panel *const	panel = &menu->object_panel.cylinder_panel;

	panel->diameter_label.f = &cylinder->diameter;
	panel->diameter_label_button.f = &cylinder->diameter;
	panel->height_label.f = &cylinder->height;
	panel->height_label_button.f = &cylinder->height;
}
