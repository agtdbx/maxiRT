/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_panel_register.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 18:40:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "minirt/app/scene/scene.h"

static void _register_position_and_direction_labels(
				t_menu *menu,
				t_cone *cone);
static void	_register_diameter_and_height_labels(
				t_menu *menu,
				t_cone *cone);

void	cone_panel_register(
			t_menu *menu,
			t_cone *cone)
{
	menu->object_panel.object_type = OBJ_CONE;
	menu->object_panel.title = menu->object_panel.cone_title;
	menu->object_panel.object_ptr = cone;
	_register_diameter_and_height_labels(menu, cone);
	_register_position_and_direction_labels(menu, cone);
}

static void _register_position_and_direction_labels(
				t_menu *menu,
				t_cone *cone)
{
	t_cone_panel *const	panel = &menu->object_panel.cone_panel;

	panel->position_label.label_x.f = &cone->pos.x;
	panel->position_label.label_y.f = &cone->pos.y;
	panel->position_label.label_z.f = &cone->pos.z;
	panel->position_label_button_x.f = &cone->pos.x;
	panel->position_label_button_y.f = &cone->pos.y;
	panel->position_label_button_z.f = &cone->pos.z;
	panel->direction_label.label_x.f = &cone->axis.x;
	panel->direction_label.label_y.f = &cone->axis.y;
	panel->direction_label.label_z.f = &cone->axis.z;
	panel->direction_label_button_x.f = &cone->axis.x;
	panel->direction_label_button_y.f = &cone->axis.y;
	panel->direction_label_button_z.f = &cone->axis.z;
}

static void	_register_diameter_and_height_labels(
				t_menu *menu,
				t_cone *cone)
{
	t_cone_panel *const	panel = &menu->object_panel.cone_panel;

	panel->diameter_label.f = &cone->diameter;
	panel->diameter_label_button.f = &cone->diameter;
	panel->height_label.f = &cone->height;
	panel->height_label_button.f = &cone->height;
}
