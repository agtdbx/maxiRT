/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:48:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/18 15:32:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

bool	object_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	if (!menu->object_panel.is_enabled)
		return (false);
	if (menu->object_panel.title != NULL)
	{
		menu->object_panel.title->instances->x = \
			menu->background->instances->x + 20;
	}
	should_redraw = false;
	color_label_draw(mlx, menu, &menu->object_panel.color_label);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.color_label_button_r);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.color_label_button_g);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.color_label_button_b);
	float_label_draw(mlx, menu, &menu->object_panel.opacity_label);
	float_label_draw(mlx, menu, &menu->object_panel.density_label);
	float_label_draw(mlx, menu, &menu->object_panel.reflection_label);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.opacity_label_button);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.density_label_button);
	should_redraw |= button_draw(mlx, menu, &menu->object_panel.reflection_label_button);
	if (menu->object_panel.object_type == OBJ_PLANE)
		should_redraw |= plane_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_SPHERE)
		should_redraw |= sphere_panel_draw(mlx, menu);
	return (should_redraw);
}
