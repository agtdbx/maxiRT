/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_panel_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:47 by damien            #+#    #+#             */
/*   Updated: 2025/01/19 15:20:14 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"
#include <stdint.h>

static const uint32_t	g_pos[2] = {20, 600};

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_direction_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_height_label(
				mlx_t *mlx,
				t_menu *menu);

void	paraboloid_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	_init_height_label(mlx, menu);
	_init_position_label(mlx, menu);
	_init_direction_label(mlx, menu);
}

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_paraboloid_panel *const	panel = &menu->object_panel.paraboloid_panel;

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

static void	_init_direction_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_paraboloid_panel *const	panel = &menu->object_panel.paraboloid_panel;

	panel->direction_label = vec3_label_init(mlx, menu, "direction: ",
			(uint32_t[2]){g_pos[0] + 180, g_pos[1]});
	button_init(mlx, &panel->direction_label_button_x,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 20});
	panel->direction_label_button_x.f = NULL;
	panel->direction_label_button_x.min = -1.0f;
	panel->direction_label_button_x.max = 1.0f;
	panel->direction_label_button_x.step = 0.001f;
	button_init(mlx, &panel->direction_label_button_y,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 40});
	panel->direction_label_button_y.f = NULL;
	panel->direction_label_button_y.min = -1.0f;
	panel->direction_label_button_y.max = 1.0f;
	panel->direction_label_button_y.step = 0.001f;
	button_init(mlx, &panel->direction_label_button_z,
		(int32_t[2]){g_pos[0] + 300, g_pos[1] + 60});
	panel->direction_label_button_z.f = NULL;
	panel->direction_label_button_z.min = -1.0f;
	panel->direction_label_button_z.max = 1.0f;
	panel->direction_label_button_z.step = 0.001f;
}

static void	_init_height_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_paraboloid_panel *const	panel = &menu->object_panel.paraboloid_panel;

	float_label_init(&panel->height_label, "height: ",
		(uint32_t[2]){g_pos[0], g_pos[1] + 120});
	button_init(mlx, &panel->height_label_button,
		(int32_t[2]){g_pos[0] + 150, g_pos[1] + 120});
	panel->height_label_button.f = NULL;
	panel->height_label_button.min = 0.0f;
	panel->height_label_button.max = 10000.0f;
	panel->height_label_button.step = 0.01f;
}
