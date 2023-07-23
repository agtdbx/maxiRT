/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_panel_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 13:02:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

static bool	_draw_position_label(
				mlx_t *mlx,
				t_menu *menu);
static bool	_draw_x_axis_label(
				mlx_t *mlx,
				t_menu *menu);
static bool	_draw_y_axis_label(
				mlx_t *mlx,
				t_menu *menu);
static bool	_draw_size_labels(
				mlx_t *mlx,
				t_menu *menu);

bool	cube_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	should_redraw |= _draw_position_label(mlx, menu);
	should_redraw |= _draw_x_axis_label(mlx, menu);
	should_redraw |= _draw_y_axis_label(mlx, menu);
	should_redraw |= _draw_size_labels(mlx, menu);
	if (should_redraw)
		cube_compute_constants_from_menu(
			(t_cube *)menu->object_panel.object_ptr);
	return (should_redraw);
}

static bool	_draw_position_label(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.position_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.position_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.position_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.position_label_button_z);
	return (should_redraw);
}

static bool	_draw_x_axis_label(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.x_axis_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.x_axis_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.x_axis_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.x_axis_label_button_z);
	return (should_redraw);
}

static bool	_draw_y_axis_label(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.y_axis_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.y_axis_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.y_axis_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.y_axis_label_button_z);
	return (should_redraw);
}

static bool	_draw_size_labels(
				mlx_t *mlx,
				t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	float_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.width_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.width_label_button);
	float_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.height_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.height_label_button);
	float_label_draw(mlx, menu,
		&menu->object_panel.cube_panel.depth_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.cube_panel.depth_label_button);
	return (should_redraw);
}
