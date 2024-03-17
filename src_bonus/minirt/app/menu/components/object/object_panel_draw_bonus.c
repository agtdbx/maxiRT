/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_draw_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:53:38 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/17 14:58:43 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene_bonus.h"

static bool	_draw_common_labels(
				mlx_t *mlx,
				t_menu *menu);

bool	object_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	if (!menu->object_panel.is_enabled)
		return (false);
	should_redraw = false;
	should_redraw |= _draw_common_labels(mlx, menu);
	if (menu->object_panel.object_type == OBJ_CONE)
		should_redraw |= cone_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_CUBE)
		should_redraw |= cube_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_PLANE)
		should_redraw |= plane_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_SPHERE)
		should_redraw |= sphere_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_CYLINDER)
		should_redraw |= cylinder_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_TRIANGLE)
		should_redraw |= triangle_panel_draw(mlx, menu);
	if (menu->object_panel.object_type == OBJ_OBJECT_FILE)
		should_redraw |= object_file_panel_draw(mlx, menu);
	return (should_redraw);
}
#include <stdio.h>
static bool	_draw_common_labels(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	if (menu->object_panel.title != NULL)
	{
		menu->object_panel.title->instances->x = \
			menu->background->instances->x + 20;
	}
	should_redraw = false;
	color_label_draw(mlx, menu, &menu->object_panel.color_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.color_label_button_r);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.color_label_button_g);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.color_label_button_b);
	float_label_draw(mlx, menu, &menu->object_panel.opacity_label);
	float_label_draw(mlx, menu, &menu->object_panel.density_label);
	float_label_draw(mlx, menu, &menu->object_panel.reflection_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.opacity_label_button);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.density_label_button);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.reflection_label_button);
	return (should_redraw);
}
