/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_panel_hide.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:51 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 16:09:46 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	paraboloid_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.paraboloid_panel.position_label);
	button_hide(&menu->object_panel.paraboloid_panel.position_label_button_x);
	button_hide(&menu->object_panel.paraboloid_panel.position_label_button_y);
	button_hide(&menu->object_panel.paraboloid_panel.position_label_button_z);
	vec3_label_hide(&menu->object_panel.paraboloid_panel.direction_label);
	button_hide(&menu->object_panel.paraboloid_panel.direction_label_button_x);
	button_hide(&menu->object_panel.paraboloid_panel.direction_label_button_y);
	button_hide(&menu->object_panel.paraboloid_panel.direction_label_button_z);
	float_label_hide(&menu->object_panel.paraboloid_panel.height_label);
	button_hide(&menu->object_panel.paraboloid_panel.height_label_button);
}
