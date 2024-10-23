/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_file_panel_show.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 14:54:33 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	object_file_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.object_file_panel.position_label);
	button_show(&menu->object_panel.object_file_panel.position_label_button_x);
	button_show(&menu->object_panel.object_file_panel.position_label_button_y);
	button_show(&menu->object_panel.object_file_panel.position_label_button_z);
	vec3_label_show(&menu->object_panel.object_file_panel.x_axis_label);
	button_show(&menu->object_panel.object_file_panel.x_axis_label_button_x);
	button_show(&menu->object_panel.object_file_panel.x_axis_label_button_y);
	button_show(&menu->object_panel.object_file_panel.x_axis_label_button_z);
	vec3_label_show(&menu->object_panel.object_file_panel.y_axis_label);
	button_show(&menu->object_panel.object_file_panel.y_axis_label_button_x);
	button_show(&menu->object_panel.object_file_panel.y_axis_label_button_y);
	button_show(&menu->object_panel.object_file_panel.y_axis_label_button_z);
	float_label_show(&menu->object_panel.object_file_panel.size_label);
	button_show(&menu->object_panel.object_file_panel.size_label_button);
}
