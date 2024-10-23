/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_panel_hide.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:09:24 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 18:36:46 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	triangle_panel_hide(
			t_menu *menu)
{
	vec3_label_hide(&menu->object_panel.triangle_panel.position_p1_label);
	button_hide(&menu->object_panel.triangle_panel.position_p1_label_button_x);
	button_hide(&menu->object_panel.triangle_panel.position_p1_label_button_y);
	button_hide(&menu->object_panel.triangle_panel.position_p1_label_button_z);
	vec3_label_hide(&menu->object_panel.triangle_panel.position_p2_label);
	button_hide(&menu->object_panel.triangle_panel.position_p2_label_button_x);
	button_hide(&menu->object_panel.triangle_panel.position_p2_label_button_y);
	button_hide(&menu->object_panel.triangle_panel.position_p2_label_button_z);
	vec3_label_hide(&menu->object_panel.triangle_panel.position_p3_label);
	button_hide(&menu->object_panel.triangle_panel.position_p3_label_button_x);
	button_hide(&menu->object_panel.triangle_panel.position_p3_label_button_y);
	button_hide(&menu->object_panel.triangle_panel.position_p3_label_button_z);
}
