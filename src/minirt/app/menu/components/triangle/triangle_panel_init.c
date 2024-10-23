/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_panel_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:10:59 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 19:34:41 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"
#include <stdint.h>

static const uint32_t	g_pos[2] = {20, 440};

static void	_init_point1_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_point2_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_point3_label(
				mlx_t *mlx,
				t_menu *menu);

void	triangle_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	_init_point1_label(mlx, menu);
	_init_point2_label(mlx, menu);
	_init_point3_label(mlx, menu);
}

static void	_init_point1_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_triangle_panel *const	panel = &menu->object_panel.triangle_panel;

	panel->position_p1_label = vec3_label_init(mlx, menu, "point 1: ", g_pos);
	button_init(mlx, &panel->position_p1_label_button_x,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 20});
	panel->position_p1_label_button_x.f = NULL;
	panel->position_p1_label_button_x.min = -10000.0f;
	panel->position_p1_label_button_x.max = 10000.0f;
	panel->position_p1_label_button_x.step = 0.01f;
	button_init(mlx, &panel->position_p1_label_button_y,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 40});
	panel->position_p1_label_button_y.f = NULL;
	panel->position_p1_label_button_y.min = -10000.0f;
	panel->position_p1_label_button_y.max = 10000.0f;
	panel->position_p1_label_button_y.step = 0.01f;
	button_init(mlx, &panel->position_p1_label_button_z,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 60});
	panel->position_p1_label_button_z.f = NULL;
	panel->position_p1_label_button_z.min = -10000.0f;
	panel->position_p1_label_button_z.max = 10000.0f;
	panel->position_p1_label_button_z.step = 0.01f;
}

static void	_init_point2_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_triangle_panel *const	panel = &menu->object_panel.triangle_panel;

	panel->position_p2_label = vec3_label_init(mlx, menu, "point 2: ",
				(uint32_t[2]){g_pos[0] + 180, g_pos[1]});
	button_init(mlx, &panel->position_p2_label_button_x,
		(int32_t[2]){g_pos[0] + 280, g_pos[1] + 20});
	panel->position_p2_label_button_x.f = NULL;
	panel->position_p2_label_button_x.min = -10000.0f;
	panel->position_p2_label_button_x.max = 10000.0f;
	panel->position_p2_label_button_x.step = 0.01f;
	button_init(mlx, &panel->position_p2_label_button_y,
		(int32_t[2]){g_pos[0] + 280, g_pos[1] + 40});
	panel->position_p2_label_button_y.f = NULL;
	panel->position_p2_label_button_y.min = -10000.0f;
	panel->position_p2_label_button_y.max = 10000.0f;
	panel->position_p2_label_button_y.step = 0.01f;
	button_init(mlx, &panel->position_p2_label_button_z,
		(int32_t[2]){g_pos[0] + 280, g_pos[1] + 60});
	panel->position_p2_label_button_z.f = NULL;
	panel->position_p2_label_button_z.min = -10000.0f;
	panel->position_p2_label_button_z.max = 10000.0f;
	panel->position_p2_label_button_z.step = 0.01f;
}

static void	_init_point3_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_triangle_panel *const	panel = &menu->object_panel.triangle_panel;

	panel->position_p3_label = vec3_label_init(mlx, menu, "point 3: ",
				(uint32_t[2]){g_pos[0], g_pos[1] + 100});
	button_init(mlx, &panel->position_p3_label_button_x,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 120});
	panel->position_p3_label_button_x.f = NULL;
	panel->position_p3_label_button_x.min = -10000.0f;
	panel->position_p3_label_button_x.max = 10000.0f;
	panel->position_p3_label_button_x.step = 0.01f;
	button_init(mlx, &panel->position_p3_label_button_y,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 140});
	panel->position_p3_label_button_y.f = NULL;
	panel->position_p3_label_button_y.min = -10000.0f;
	panel->position_p3_label_button_y.max = 10000.0f;
	panel->position_p3_label_button_y.step = 0.01f;
	button_init(mlx, &panel->position_p3_label_button_z,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 160});
	panel->position_p3_label_button_z.f = NULL;
	panel->position_p3_label_button_z.min = -10000.0f;
	panel->position_p3_label_button_z.max = 10000.0f;
	panel->position_p3_label_button_z.step = 0.01f;
}
