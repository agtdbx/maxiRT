/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_show.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:54:11 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:48:12 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/color/color.h"

void	light_panel_show(
			t_menu *menu)
{
	if (menu->light_panel.title != NULL)
	{
		menu->light_panel.title->enabled = true;
	}
	color_label_show(&menu->light_panel.color_label);
	button_show(&menu->light_panel.color_label_button_r);
	button_show(&menu->light_panel.color_label_button_g);
	button_show(&menu->light_panel.color_label_button_b);
	float_label_show(&menu->light_panel.intensity_label);
	button_show(&menu->light_panel.intensity_label_button);
	vec3_label_show(&menu->light_panel.position_label);
	button_show(&menu->light_panel.position_label_button_x);
	button_show(&menu->light_panel.position_label_button_y);
	button_show(&menu->light_panel.position_label_button_z);
}
