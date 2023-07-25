/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_hide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:49:54 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 14:08:30 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "minirt/app/utils/color/color.h"

void	object_panel_hide(
			t_menu *menu)
{
	if (menu->object_panel.title != NULL)
		menu->object_panel.title->enabled = false;
	color_label_hide(&menu->object_panel.color_label);
	button_hide(&menu->object_panel.color_label_button_r);
	button_hide(&menu->object_panel.color_label_button_g);
	button_hide(&menu->object_panel.color_label_button_b);
	float_label_hide(&menu->object_panel.opacity_label);
	float_label_hide(&menu->object_panel.density_label);
	float_label_hide(&menu->object_panel.reflection_label);
	button_hide(&menu->object_panel.opacity_label_button);
	button_hide(&menu->object_panel.density_label_button);
	button_hide(&menu->object_panel.reflection_label_button);
	plane_panel_hide(menu);
	sphere_panel_hide(menu);
	cylinder_panel_hide(menu);
}
