/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:49:54 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/17 19:33:35 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	light_panel_hide(
			t_menu *menu)
{
	if (menu->light_panel.title != NULL)
	{
		menu->light_panel.title->enabled = false;
		menu->light_panel.title_parallel->enabled = false;
	}
	color_label_hide(&menu->light_panel.color_label);
	button_hide(&menu->light_panel.color_label_button_r);
	button_hide(&menu->light_panel.color_label_button_g);
	button_hide(&menu->light_panel.color_label_button_b);
	float_label_hide(&menu->light_panel.intensity_label);
	button_hide(&menu->light_panel.intensity_label_button);
	vec3_label_hide(&menu->light_panel.position_label);
	button_hide(&menu->light_panel.position_label_button_x);
	button_hide(&menu->light_panel.position_label_button_y);
	button_hide(&menu->light_panel.position_label_button_z);
	vec3_label_hide(&menu->light_panel.direction_label);
	button_hide(&menu->light_panel.direction_label_button_x);
	button_hide(&menu->light_panel.direction_label_button_y);
	button_hide(&menu->light_panel.direction_label_button_z);
	float_label_hide(&menu->light_panel.angle_label);
	button_hide(&menu->light_panel.angle_button);
}
