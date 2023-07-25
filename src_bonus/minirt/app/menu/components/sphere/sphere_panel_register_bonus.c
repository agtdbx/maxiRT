/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_register.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:57:08 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 15:31:45 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "minirt/app/scene/scene_bonus.h"

void	sphere_panel_register(
			t_menu *menu,
			t_sphere *sphere)
{
	menu->object_panel.object_type = OBJ_SPHERE;
	menu->object_panel.title = menu->object_panel.sphere_title;
	menu->object_panel.object_ptr = sphere;
	menu->object_panel.sphere_label.position_label.label_x.f = &sphere->pos.x;
	menu->object_panel.sphere_label.position_label.label_y.f = &sphere->pos.y;
	menu->object_panel.sphere_label.position_label.label_z.f = &sphere->pos.z;
	menu->object_panel.sphere_label.diameter_label.f = &sphere->diameter;
	menu->object_panel.sphere_label.position_label_button_x.f = &sphere->pos.x;
	menu->object_panel.sphere_label.position_label_button_y.f = &sphere->pos.y;
	menu->object_panel.sphere_label.position_label_button_z.f = &sphere->pos.z;
	menu->object_panel.sphere_label.diameter_label_button.f = &sphere->diameter;
}
