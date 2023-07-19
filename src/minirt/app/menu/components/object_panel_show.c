/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_show.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:54:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 17:41:33 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"

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
	if (menu->object_panel.object_type == OBJ_SPHERE)
		sphere_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_PLANE)
		plane_panel_show(menu);
	if (menu->object_panel.object_type == OBJ_CYLINDER)
		cylinder_panel_show(menu);
}
