/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_show_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:54:11 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 15:01:24 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/color/color_bonus.h"

void	object_panel_show(
			t_menu *menu)
{
	if (menu->object_panel.title != NULL)
	{
		menu->object_panel.title->enabled = true;
	}
	color_label_show(&menu->object_panel.color_label);
	button_show(&menu->object_panel.color_label_button_r);
	button_show(&menu->object_panel.color_label_button_g);
	button_show(&menu->object_panel.color_label_button_b);
	float_label_show(&menu->object_panel.opacity_label);
	float_label_show(&menu->object_panel.density_label);
	float_label_show(&menu->object_panel.reflection_label);
	button_show(&menu->object_panel.opacity_label_button);
	button_show(&menu->object_panel.density_label_button);
	button_show(&menu->object_panel.reflection_label_button);
	if (menu->object_panel.object_type == OBJ_CONE)
		cone_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_CUBE)
		cube_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_PLANE)
		plane_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_SPHERE)
		sphere_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_CYLINDER)
		cylinder_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_TRIANGLE)
		triangle_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_OBJECT_FILE)
		object_file_panel_show(menu);
}
