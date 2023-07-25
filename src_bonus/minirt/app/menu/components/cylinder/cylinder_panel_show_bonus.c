/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_panel_show.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 16:39:46 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	cylinder_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.cylinder_panel.position_label);
	button_show(&menu->object_panel.cylinder_panel.position_label_button_x);
	button_show(&menu->object_panel.cylinder_panel.position_label_button_y);
	button_show(&menu->object_panel.cylinder_panel.position_label_button_z);
	vec3_label_show(&menu->object_panel.cylinder_panel.direction_label);
	button_show(&menu->object_panel.cylinder_panel.direction_label_button_x);
	button_show(&menu->object_panel.cylinder_panel.direction_label_button_y);
	button_show(&menu->object_panel.cylinder_panel.direction_label_button_z);
	float_label_show(&menu->object_panel.cylinder_panel.diameter_label);
	button_show(&menu->object_panel.cylinder_panel.diameter_label_button);
	float_label_show(&menu->object_panel.cylinder_panel.height_label);
	button_show(&menu->object_panel.cylinder_panel.height_label_button);
}
