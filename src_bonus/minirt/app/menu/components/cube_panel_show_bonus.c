/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_panel_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/20 16:51:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	cube_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.cube_panel.position_label);
	button_show(&menu->object_panel.cube_panel.position_label_button_x);
	button_show(&menu->object_panel.cube_panel.position_label_button_y);
	button_show(&menu->object_panel.cube_panel.position_label_button_z);
	vec3_label_show(&menu->object_panel.cube_panel.x_axis_label);
	button_show(&menu->object_panel.cube_panel.x_axis_label_button_x);
	button_show(&menu->object_panel.cube_panel.x_axis_label_button_y);
	button_show(&menu->object_panel.cube_panel.x_axis_label_button_z);
	vec3_label_show(&menu->object_panel.cube_panel.y_axis_label);
	button_show(&menu->object_panel.cube_panel.y_axis_label_button_x);
	button_show(&menu->object_panel.cube_panel.y_axis_label_button_y);
	button_show(&menu->object_panel.cube_panel.y_axis_label_button_z);
	float_label_show(&menu->object_panel.cube_panel.width_label);
	button_show(&menu->object_panel.cube_panel.width_label_button);
	float_label_show(&menu->object_panel.cube_panel.height_label);
	button_show(&menu->object_panel.cube_panel.height_label_button);
	float_label_show(&menu->object_panel.cube_panel.depth_label);
	button_show(&menu->object_panel.cube_panel.depth_label_button);
}
