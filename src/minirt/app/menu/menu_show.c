/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/17 23:27:00 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

static void	color_filter_show(
				t_menu *menu);

void	menu_show(
			t_menu *menu)
{
	menu->is_visible = true;
	if (menu->background != NULL)
		menu->background->enabled = true;
	camera_label_show(menu);
	color_filter_show(menu);
	ambient_label_show(menu);
	if (menu->object_panel.is_enabled)
		object_panel_show(menu);
	if (menu->light_panel.is_enabled)
		light_panel_show(menu);
}

static void	color_filter_show(
				t_menu *menu)
{
	vec3_label_show(&menu->color_filter_label);
	button_show(&menu->color_filter_button_r);
	button_show(&menu->color_filter_button_g);
	button_show(&menu->color_filter_button_b);
}
