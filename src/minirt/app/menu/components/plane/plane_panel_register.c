/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_panel_register.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 12:23:34 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "minirt/app/scene/scene.h"

void	plane_panel_register(
			t_menu *menu,
			t_plane *plane)
{
	menu->object_panel.object_type = OBJ_PLANE;
	menu->object_panel.title = menu->object_panel.plane_title;
	menu->object_panel.object_ptr = plane;
	menu->object_panel.plane_panel.position_label.label_x.f = &plane->pos.x;
	menu->object_panel.plane_panel.position_label.label_y.f = &plane->pos.y;
	menu->object_panel.plane_panel.position_label.label_z.f = &plane->pos.z;
	menu->object_panel.plane_panel.position_label_button_x.f = &plane->pos.x;
	menu->object_panel.plane_panel.position_label_button_y.f = &plane->pos.y;
	menu->object_panel.plane_panel.position_label_button_z.f = &plane->pos.z;
	menu->object_panel.plane_panel.direction_label.label_x.f = &plane->normal.x;
	menu->object_panel.plane_panel.direction_label.label_y.f = &plane->normal.y;
	menu->object_panel.plane_panel.direction_label.label_z.f = &plane->normal.z;
	menu->object_panel.plane_panel.direction_label_button_x.f
		= &plane->normal.x;
	menu->object_panel.plane_panel.direction_label_button_y.f
		= &plane->normal.y;
	menu->object_panel.plane_panel.direction_label_button_z.f
		= &plane->normal.z;
}
