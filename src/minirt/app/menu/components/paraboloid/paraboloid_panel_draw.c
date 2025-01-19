/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_panel_draw.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:31 by damien            #+#    #+#             */
/*   Updated: 2025/01/16 16:12:42 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

static bool	_draw_position_and_direction_labels(
				mlx_t *mlx,
				t_menu *menu);
static bool	_draw_height_label(
				mlx_t *mlx,
				t_menu *menu);

bool	paraboloid_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	should_redraw |= _draw_position_and_direction_labels(mlx, menu);
	should_redraw |= _draw_height_label(mlx, menu);
	if (should_redraw)
	{
		paraboloid_compute_constants(
			(t_paraboloid *)menu->object_panel.object_ptr);
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
		&menu->object_panel.paraboloid_panel.position_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.position_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.position_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.position_label_button_z);
	vec3_label_draw(mlx, menu,
		&menu->object_panel.paraboloid_panel.direction_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.direction_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.direction_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.direction_label_button_z);
	return (should_redraw);
}

static bool	_draw_height_label(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	float_label_draw(mlx, menu,
		&menu->object_panel.paraboloid_panel.height_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.paraboloid_panel.height_label_button);
	return (should_redraw);
}
