/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_panel_hide_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:51:48 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 14:51:56 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	object_file_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.object_file_panel.position_label);
	button_hide(&menu->object_panel.object_file_panel.position_label_button_x);
	button_hide(&menu->object_panel.object_file_panel.position_label_button_y);
	button_hide(&menu->object_panel.object_file_panel.position_label_button_z);
	vec3_label_hide(&menu->object_panel.object_file_panel.x_axis_label);
	button_hide(&menu->object_panel.object_file_panel.x_axis_label_button_x);
	button_hide(&menu->object_panel.object_file_panel.x_axis_label_button_y);
	button_hide(&menu->object_panel.object_file_panel.x_axis_label_button_z);
	vec3_label_hide(&menu->object_panel.object_file_panel.y_axis_label);
	button_hide(&menu->object_panel.object_file_panel.y_axis_label_button_x);
	button_hide(&menu->object_panel.object_file_panel.y_axis_label_button_y);
	button_hide(&menu->object_panel.object_file_panel.y_axis_label_button_z);
	float_label_hide(&menu->object_panel.object_file_panel.size_label);
	button_hide(&menu->object_panel.object_file_panel.size_label_button);
}
