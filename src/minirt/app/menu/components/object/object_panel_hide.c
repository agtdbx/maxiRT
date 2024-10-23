/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_hide.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:49:54 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 14:59:45 by auguste          ###   ########.fr       */
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
	cone_panel_hide(menu);
	cube_panel_hide(menu);
	plane_panel_hide(menu);
	sphere_panel_hide(menu);
	cylinder_panel_hide(menu);
	triangle_panel_hide(menu);
	object_file_panel_hide(menu);
}
