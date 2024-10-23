/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_panel_show.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:01:14 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 19:36:39 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

void	triangle_panel_show(
			t_menu *menu)
{
	vec3_label_show(&menu->object_panel.triangle_panel.position_p1_label);
	button_show(&menu->object_panel.triangle_panel.position_p1_label_button_x);
	button_show(&menu->object_panel.triangle_panel.position_p1_label_button_y);
	button_show(&menu->object_panel.triangle_panel.position_p1_label_button_z);
	vec3_label_show(&menu->object_panel.triangle_panel.position_p2_label);
	button_show(&menu->object_panel.triangle_panel.position_p2_label_button_x);
	button_show(&menu->object_panel.triangle_panel.position_p2_label_button_y);
	button_show(&menu->object_panel.triangle_panel.position_p2_label_button_z);
	vec3_label_show(&menu->object_panel.triangle_panel.position_p3_label);
	button_show(&menu->object_panel.triangle_panel.position_p3_label_button_x);
	button_show(&menu->object_panel.triangle_panel.position_p3_label_button_y);
	button_show(&menu->object_panel.triangle_panel.position_p3_label_button_z);
}
