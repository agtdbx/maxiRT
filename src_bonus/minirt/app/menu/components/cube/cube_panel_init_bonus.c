/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_panel_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:10:59 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 15:28:48 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"
#include <stdint.h>

static const uint32_t	g_pos[2] = {20, 440};

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel);
static void	_init_x_axis_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel);
static void	_init_y_axis_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel);
static void	_init_size_labels(
				mlx_t *mlx,
				t_cube_panel *const	panel);

void	cube_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	t_cube_panel *const	panel = &menu->object_panel.cube_panel;

	_init_position_label(mlx, menu, panel);
	_init_x_axis_label(mlx, menu, panel);
	_init_y_axis_label(mlx, menu, panel);
	_init_size_labels(mlx, panel);
}

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel)
{
	panel->position_label = vec3_label_init(mlx, menu, "position: ", g_pos);
	button_init(mlx, &panel->position_label_button_x,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 20});
	panel->position_label_button_x.f = NULL;
	panel->position_label_button_x.min = -10000.0f;
	panel->position_label_button_x.max = 10000.0f;
	panel->position_label_button_x.step = 0.01f;
	button_init(mlx, &panel->position_label_button_y,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 40});
	panel->position_label_button_y.f = NULL;
	panel->position_label_button_y.min = -10000.0f;
	panel->position_label_button_y.max = 10000.0f;
	panel->position_label_button_y.step = 0.01f;
	button_init(mlx, &panel->position_label_button_z,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 60});
	panel->position_label_button_z.f = NULL;
	panel->position_label_button_z.min = -10000.0f;
	panel->position_label_button_z.max = 10000.0f;
	panel->position_label_button_z.step = 0.01f;
}

static void	_init_x_axis_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel)
{
	panel->x_axis_label = vec3_label_init(mlx, menu, "x_axis: ",
			(uint32_t[2]){g_pos[0] + 180, g_pos[1]});
	button_init(mlx, &panel->x_axis_label_button_x,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 20});
	panel->x_axis_label_button_x.f = NULL;
	panel->x_axis_label_button_x.min = -1.0f;
	panel->x_axis_label_button_x.max = 1.0f;
	panel->x_axis_label_button_x.step = 0.0001f;
	button_init(mlx, &panel->x_axis_label_button_y,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 40});
	panel->x_axis_label_button_y.f = NULL;
	panel->x_axis_label_button_y.min = -1.0f;
	panel->x_axis_label_button_y.max = 1.0f;
	panel->x_axis_label_button_y.step = 0.0001f;
	button_init(mlx, &panel->x_axis_label_button_z,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 60});
	panel->x_axis_label_button_z.f = NULL;
	panel->x_axis_label_button_z.min = -1.0f;
	panel->x_axis_label_button_z.max = 1.0f;
	panel->x_axis_label_button_z.step = 0.0001f;
}

static void	_init_y_axis_label(
				mlx_t *mlx,
				t_menu *menu,
				t_cube_panel *const	panel)
{
	panel->y_axis_label = vec3_label_init(mlx, menu, "y_axis: ",
			(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 100});
	button_init(mlx, &panel->y_axis_label_button_x,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 120});
	panel->y_axis_label_button_x.f = NULL;
	panel->y_axis_label_button_x.min = -1.0f;
	panel->y_axis_label_button_x.max = 1.0f;
	panel->y_axis_label_button_x.step = 0.0001f;
	button_init(mlx, &panel->y_axis_label_button_y,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 140});
	panel->y_axis_label_button_y.f = NULL;
	panel->y_axis_label_button_y.min = -1.0f;
	panel->y_axis_label_button_y.max = 1.0f;
	panel->y_axis_label_button_y.step = 0.0001f;
	button_init(mlx, &panel->y_axis_label_button_z,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 160});
	panel->y_axis_label_button_z.f = NULL;
	panel->y_axis_label_button_z.min = -1.0f;
	panel->y_axis_label_button_z.max = 1.0f;
	panel->y_axis_label_button_z.step = 0.0001f;
}

static void	_init_size_labels(
				mlx_t *mlx,
				t_cube_panel *const	panel)
{
	float_label_init(&panel->width_label, "width: ",
		(uint32_t[2]){g_pos[0], g_pos[1] + 120});
	button_init(mlx, &panel->width_label_button,
		(int32_t[2]){g_pos[0] + 130, g_pos[1] + 120});
	panel->width_label_button.f = NULL;
	panel->width_label_button.min = 0.0f;
	panel->width_label_button.max = 10000.0f;
	panel->width_label_button.step = 0.01f;
	float_label_init(&panel->height_label, "height: ",
		(uint32_t[2]){g_pos[0], g_pos[1] + 140});
	button_init(mlx, &panel->height_label_button,
		(int32_t[2]){g_pos[0] + 130, g_pos[1] + 140});
	panel->height_label_button.f = NULL;
	panel->height_label_button.min = 0.0f;
	panel->height_label_button.max = 10000.0f;
	panel->height_label_button.step = 0.01f;
	float_label_init(&panel->depth_label, "depth: ",
		(uint32_t[2]){g_pos[0], g_pos[1] + 160});
	button_init(mlx, &panel->depth_label_button,
		(int32_t[2]){g_pos[0] + 130, g_pos[1] + 160});
	panel->depth_label_button.f = NULL;
	panel->depth_label_button.min = 0.0f;
	panel->depth_label_button.max = 10000.0f;
	panel->depth_label_button.step = 0.01f;
}
