/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_panel_register.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 21:08:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/scene/scene_bonus.h"

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
