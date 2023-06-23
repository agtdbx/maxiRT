/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:26 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/23 19:01:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"

static void	_color_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_color_label *label);

static void	_float_labels_init(
				t_object_panel *panel);

void	object_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	menu->object_panel.is_enabled = false;
	menu->object_panel.title = NULL;
	menu->object_panel.sphere_title = mlx_put_string(mlx, "-- Sphere --", 
			menu->background->instances->x + 20, 300);
	_color_label_init(mlx, menu, &menu->object_panel.color_label);
	_float_labels_init(&menu->object_panel);
}

static void	_color_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_color_label *label)
{
	label->title = "color:";
	label->x = 20;
	label->y = 330;
	label->img_title = mlx_put_string(
			mlx, label->title,
			label->x + menu->background->instances->x,
			label->y);
	label->label_r.prefix = "r: ";
	label->label_r.x = label->x;
	label->label_r.y = label->y + 20;
	label->label_r.f = NULL;
	label->label_r.img = NULL;
	label->label_g.prefix = "g: ";
	label->label_g.x = label->x;
	label->label_g.y = label->y + 40;
	label->label_g.f = NULL;
	label->label_g.img = NULL;
	label->label_b.prefix = "b: ";
	label->label_b.x = label->x;
	label->label_b.y = label->y + 60;
	label->label_b.f = NULL;
	label->label_b.img = NULL;
}

static void	_float_labels_init(
		t_object_panel *panel)
{
	panel->opacity_label.prefix = "opacity: ";
	panel->opacity_label.x = 200;
	panel->opacity_label.y = 330;
	panel->opacity_label.f = NULL;
	panel->opacity_label.img = NULL;
	panel->density_label.prefix = "density: ";
	panel->density_label.x = 200;
	panel->density_label.y = 360;
	panel->density_label.f = NULL;
	panel->density_label.img = NULL;
	panel->reflection_label.prefix = "reflection: ";
	panel->reflection_label.x = 200;
	panel->reflection_label.y = 390;
	panel->reflection_label.f = NULL;
	panel->reflection_label.img = NULL;
}
