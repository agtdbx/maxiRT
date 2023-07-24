/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_register.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:11:36 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:51:35 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene_bonus.h"

void	light_panel_register(
			t_menu *menu,
			t_light *light)
{
	object_panel_hide(menu);
	menu->light_panel.is_enabled = true;
	menu->object_panel.is_enabled = false;
	menu->light_panel.color_label.label_r.f = &light->color.r;
	menu->light_panel.color_label.label_g.f = &light->color.g;
	menu->light_panel.color_label.label_b.f = &light->color.b;
	menu->light_panel.color_label_button_r.f = &light->color.r;
	menu->light_panel.color_label_button_g.f = &light->color.g;
	menu->light_panel.color_label_button_b.f = &light->color.b;
	menu->light_panel.intensity_label.f = &light->brightness;
	menu->light_panel.intensity_label_button.f = &light->brightness;
	menu->light_panel.position_label.label_x.f = &light->pos.x;
	menu->light_panel.position_label.label_y.f = &light->pos.y;
	menu->light_panel.position_label.label_z.f = &light->pos.z;
	menu->light_panel.position_label_button_x.f = &light->pos.x;
	menu->light_panel.position_label_button_y.f = &light->pos.y;
	menu->light_panel.position_label_button_z.f = &light->pos.z;
	light_panel_show(menu);
}
