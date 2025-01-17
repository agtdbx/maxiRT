/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_show.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:54:11 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/17 20:00:19 by aderouba         ###   ########.fr       */
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
		if (menu->light_panel.light_ptr->parallel)
		{
			menu->light_panel.title_parallel->enabled = true;
			menu->light_panel.title->enabled = false;
		}
		else
		{
			menu->light_panel.title_parallel->enabled = false;
			menu->light_panel.title->enabled = true;
		}
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
	if (menu->light_panel.light_ptr->parallel)
	{
		vec3_label_show(&menu->light_panel.direction_label);
		button_show(&menu->light_panel.direction_label_button_x);
		button_show(&menu->light_panel.direction_label_button_y);
		button_show(&menu->light_panel.direction_label_button_z);
		button_show(&menu->light_panel.angle_button);
		float_label_show(&menu->light_panel.angle_label);
	}
	else
	{
		vec3_label_hide(&menu->light_panel.direction_label);
		button_hide(&menu->light_panel.direction_label_button_x);
		button_hide(&menu->light_panel.direction_label_button_y);
		button_hide(&menu->light_panel.direction_label_button_z);
		button_hide(&menu->light_panel.angle_button);
		float_label_hide(&menu->light_panel.angle_label);
	}

}
