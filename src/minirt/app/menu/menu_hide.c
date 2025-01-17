/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_hide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:42:34 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/17 23:26:03 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

static void	color_filter_hide(
				t_menu *menu);

void	menu_hide(
			t_menu *menu)
{
	menu->is_visible = false;
	if (menu->background != NULL)
		menu->background->enabled = false;
	camera_label_hide(menu);
	color_filter_hide(menu);
	ambient_label_hide(menu);
	object_panel_hide(menu);
	light_panel_hide(menu);
}

static void	color_filter_hide(
				t_menu *menu)
{
	vec3_label_hide(&menu->color_filter_label);
	button_hide(&menu->color_filter_button_r);
	button_hide(&menu->color_filter_button_g);
	button_hide(&menu->color_filter_button_b);
}
