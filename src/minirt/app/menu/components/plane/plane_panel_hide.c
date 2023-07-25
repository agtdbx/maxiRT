/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_panel_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:09:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/18 15:09:42 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	plane_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.plane_panel.position_label);
	button_hide(&menu->object_panel.plane_panel.position_label_button_x);
	button_hide(&menu->object_panel.plane_panel.position_label_button_y);
	button_hide(&menu->object_panel.plane_panel.position_label_button_z);
	vec3_label_hide(&menu->object_panel.plane_panel.direction_label);
	button_hide(&menu->object_panel.plane_panel.direction_label_button_x);
	button_hide(&menu->object_panel.plane_panel.direction_label_button_y);
	button_hide(&menu->object_panel.plane_panel.direction_label_button_z);
}
