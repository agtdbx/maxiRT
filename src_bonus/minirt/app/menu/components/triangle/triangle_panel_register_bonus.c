/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_panel_register_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 19:39:41 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/scene/scene_bonus.h"

void	triangle_panel_register(
			t_menu *menu,
			t_triangle *triangle)
{
	menu->object_panel.object_type = OBJ_TRIANGLE;
	menu->object_panel.title = menu->object_panel.triangle_title;
	menu->object_panel.object_ptr = triangle;
	menu->object_panel.triangle_panel.position_p1_label.label_x.f = &triangle->point1.x;
	menu->object_panel.triangle_panel.position_p1_label.label_y.f = &triangle->point1.y;
	menu->object_panel.triangle_panel.position_p1_label.label_z.f = &triangle->point1.z;
	menu->object_panel.triangle_panel.position_p1_label_button_x.f = &triangle->point1.x;
	menu->object_panel.triangle_panel.position_p1_label_button_y.f = &triangle->point1.y;
	menu->object_panel.triangle_panel.position_p1_label_button_z.f = &triangle->point1.z;
	menu->object_panel.triangle_panel.position_p2_label.label_x.f = &triangle->point2.x;
	menu->object_panel.triangle_panel.position_p2_label.label_y.f = &triangle->point2.y;
	menu->object_panel.triangle_panel.position_p2_label.label_z.f = &triangle->point2.z;
	menu->object_panel.triangle_panel.position_p2_label_button_x.f = &triangle->point2.x;
	menu->object_panel.triangle_panel.position_p2_label_button_y.f = &triangle->point2.y;
	menu->object_panel.triangle_panel.position_p2_label_button_z.f = &triangle->point2.z;
	menu->object_panel.triangle_panel.position_p3_label.label_x.f = &triangle->point3.x;
	menu->object_panel.triangle_panel.position_p3_label.label_y.f = &triangle->point3.y;
	menu->object_panel.triangle_panel.position_p3_label.label_z.f = &triangle->point3.z;
	menu->object_panel.triangle_panel.position_p3_label_button_x.f = &triangle->point3.x;
	menu->object_panel.triangle_panel.position_p3_label_button_y.f = &triangle->point3.y;
	menu->object_panel.triangle_panel.position_p3_label_button_z.f = &triangle->point3.z;
}
