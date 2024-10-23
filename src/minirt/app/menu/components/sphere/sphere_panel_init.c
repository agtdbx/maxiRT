/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:10:59 by tdubois           #+#    #+#             */
/*   Updated: 2024/03/11 19:21:15 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"
#include <stdint.h>

static const uint32_t	g_pos[2] = {20, 440};

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_diameter_label(
				mlx_t *mlx,
				t_menu *menu);

void	sphere_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	_init_position_label(mlx, menu);
	_init_diameter_label(mlx, menu);
}

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_sphere_panel *const	panel = &menu->object_panel.sphere_label;

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

static void	_init_diameter_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_sphere_panel *const	panel = &menu->object_panel.sphere_label;

	float_label_init(&panel->diameter_label, "diameter: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1]});
	button_init(mlx, &panel->diameter_label_button,
		(int32_t[2]){g_pos[0] + 335, g_pos[1]});
	panel->diameter_label_button.f = NULL;
	panel->diameter_label_button.min = 0.0f;
	panel->diameter_label_button.max = 10000.0f;
	panel->diameter_label_button.step = 0.01f;
}
