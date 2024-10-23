/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_panel_show.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 19:10:09 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

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
