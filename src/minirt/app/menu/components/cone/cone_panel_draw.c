/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_panel_draw.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:47:40 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

static bool	_draw_position_and_direction_labels(
				mlx_t *mlx,
				t_menu *menu);
static bool	_draw_diameter_and_height_labels(
				mlx_t *mlx,
				t_menu *menu);

bool	cone_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	should_redraw |= _draw_position_and_direction_labels(mlx, menu);
	should_redraw |= _draw_diameter_and_height_labels(mlx, menu);
	if (should_redraw)
	{
		cone_compute_constants(
			(t_cone *)menu->object_panel.object_ptr,
			menu->object_panel.object_bbox);
		compute_scene_binary_tree(menu->scene);
	}
	return (should_redraw);
}

static bool	_draw_position_and_direction_labels(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu,
		&menu->object_panel.cone_panel.position_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.position_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.position_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.position_label_button_z);
	vec3_label_draw(mlx, menu,
		&menu->object_panel.cone_panel.direction_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.direction_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.direction_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.direction_label_button_z);
	return (should_redraw);
}

static bool	_draw_diameter_and_height_labels(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	float_label_draw(mlx, menu,
		&menu->object_panel.cone_panel.diameter_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.diameter_label_button);
	float_label_draw(mlx, menu,
		&menu->object_panel.cone_panel.height_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cone_panel.height_label_button);
	return (should_redraw);
}
