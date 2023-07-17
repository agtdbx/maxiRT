/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_hide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:49:54 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:48:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	light_panel_hide(
			t_menu *menu)
{
	if (menu->light_panel.title != NULL)
		menu->light_panel.title->enabled = false;
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
}
