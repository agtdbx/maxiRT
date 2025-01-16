/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_panel_register.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:55:10 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 16:21:17 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "minirt/app/scene/scene.h"

static void	_register_position_and_direction_labels(
				t_menu *menu,
				t_paraboloid *paraboloid);
static void	_register_height_label(
				t_menu *menu,
				t_paraboloid *paraboloid);

void	paraboloid_panel_register(
			t_menu *menu,
			t_paraboloid *paraboloid)
{
	menu->object_panel.object_type = OBJ_PARABOLOID;
	menu->object_panel.title = menu->object_panel.paraboloid_title;
	menu->object_panel.object_ptr = paraboloid;
	_register_height_label(menu, paraboloid);
	_register_position_and_direction_labels(menu, paraboloid);
}

static void	_register_position_and_direction_labels(
				t_menu *menu,
				t_paraboloid *paraboloid)
{
	t_paraboloid_panel *const	panel = &menu->object_panel.paraboloid_panel;

	panel->position_label.label_x.f = &paraboloid->pos.x;
	panel->position_label.label_y.f = &paraboloid->pos.y;
	panel->position_label.label_z.f = &paraboloid->pos.z;
	panel->position_label_button_x.f = &paraboloid->pos.x;
	panel->position_label_button_y.f = &paraboloid->pos.y;
	panel->position_label_button_z.f = &paraboloid->pos.z;
	panel->direction_label.label_x.f = &paraboloid->dir.x;
	panel->direction_label.label_y.f = &paraboloid->dir.y;
	panel->direction_label.label_z.f = &paraboloid->dir.z;
	panel->direction_label_button_x.f = &paraboloid->dir.x;
	panel->direction_label_button_y.f = &paraboloid->dir.y;
	panel->direction_label_button_z.f = &paraboloid->dir.z;
}

static void	_register_height_label(
				t_menu *menu,
				t_paraboloid *paraboloid)
{
	t_paraboloid_panel *const	panel = &menu->object_panel.paraboloid_panel;

	panel->height_label.f = &paraboloid->k;
	panel->height_label_button.f = &paraboloid->k;
}

