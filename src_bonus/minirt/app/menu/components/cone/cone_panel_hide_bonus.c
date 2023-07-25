/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_panel_hide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 18:31:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	cone_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.cone_panel.position_label);
	button_hide(&menu->object_panel.cone_panel.position_label_button_x);
	button_hide(&menu->object_panel.cone_panel.position_label_button_y);
	button_hide(&menu->object_panel.cone_panel.position_label_button_z);
	vec3_label_hide(&menu->object_panel.cone_panel.direction_label);
	button_hide(&menu->object_panel.cone_panel.direction_label_button_x);
	button_hide(&menu->object_panel.cone_panel.direction_label_button_y);
	button_hide(&menu->object_panel.cone_panel.direction_label_button_z);
	float_label_hide(&menu->object_panel.cone_panel.diameter_label);
	button_hide(&menu->object_panel.cone_panel.diameter_label_button);
	float_label_hide(&menu->object_panel.cone_panel.height_label);
	button_hide(&menu->object_panel.cone_panel.height_label_button);
}
