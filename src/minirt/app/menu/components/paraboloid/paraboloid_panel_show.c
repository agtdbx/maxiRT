/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_panel_show.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:55:14 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 16:11:47 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	paraboloid_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.paraboloid_panel.position_label);
	button_show(&menu->object_panel.paraboloid_panel.position_label_button_x);
	button_show(&menu->object_panel.paraboloid_panel.position_label_button_y);
	button_show(&menu->object_panel.paraboloid_panel.position_label_button_z);
	vec3_label_show(&menu->object_panel.paraboloid_panel.direction_label);
	button_show(&menu->object_panel.paraboloid_panel.direction_label_button_x);
	button_show(&menu->object_panel.paraboloid_panel.direction_label_button_y);
	button_show(&menu->object_panel.paraboloid_panel.direction_label_button_z);
	float_label_show(&menu->object_panel.paraboloid_panel.height_label);
	button_show(&menu->object_panel.paraboloid_panel.height_label_button);
}
