/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_register.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:11:36 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 17:36:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

static void _register_common_labels(
				t_menu *menu,
				t_object *object);

void	object_panel_register(
			t_menu *menu,
			t_object *object)
{
	light_panel_hide(menu);
	object_panel_hide(menu);
	menu->light_panel.is_enabled = false;
	menu->object_panel.is_enabled = true;
	_register_common_labels(menu, object);
	if (object->type == OBJ_SPHERE)
	{
		sphere_panel_register(menu, &object->value.as_sphere);
		sphere_panel_show(menu);
	}
	if (object->type == OBJ_PLANE)
	{
		plane_panel_register(menu, &object->value.as_plane);
		plane_panel_show(menu);
	}
	if (object->type == OBJ_CYLINDER)
	{
		cylinder_panel_register(menu, &object->value.as_cylinder);
		cylinder_panel_show(menu);
	}
	object_panel_show(menu);
}

static void _register_common_labels(
				t_menu *menu,
				t_object *object)
{
	menu->object_panel.color_label.label_r.f = &object->color.r;
	menu->object_panel.color_label.label_g.f = &object->color.g;
	menu->object_panel.color_label.label_b.f = &object->color.b;
	menu->object_panel.color_label_button_r.f = &object->color.r;
	menu->object_panel.color_label_button_g.f = &object->color.g;
	menu->object_panel.color_label_button_b.f = &object->color.b;
	menu->object_panel.opacity_label.f = &object->opacity;
	menu->object_panel.density_label.f = &object->density;
	menu->object_panel.reflection_label.f = &object->reflection;
	menu->object_panel.opacity_label_button.f = &object->opacity;
	menu->object_panel.density_label_button.f = &object->density;
	menu->object_panel.reflection_label_button.f = &object->reflection;
}
