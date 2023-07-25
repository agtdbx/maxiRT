/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_panel_show.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/18 15:09:00 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

void	plane_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.plane_panel.position_label);
	button_show(&menu->object_panel.plane_panel.position_label_button_x);
	button_show(&menu->object_panel.plane_panel.position_label_button_y);
	button_show(&menu->object_panel.plane_panel.position_label_button_z);
	vec3_label_show(&menu->object_panel.plane_panel.direction_label);
	button_show(&menu->object_panel.plane_panel.direction_label_button_x);
	button_show(&menu->object_panel.plane_panel.direction_label_button_y);
	button_show(&menu->object_panel.plane_panel.direction_label_button_z);
}
