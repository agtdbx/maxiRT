/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:26 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 21:17:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"

static const uint32_t	g_pos[2] = {20, 310};

static void	_init_color_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_intensity_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu);

void	light_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	t_light_panel *const	panel = &menu->light_panel;

	panel->is_enabled = false;
	panel->title = mlx_put_string(mlx, "-- Light --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	_init_color_label(mlx, menu);
	_init_intensity_label(mlx, menu);
	_init_position_label(mlx, menu);//TODO
}

static void	_init_color_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_light_panel *const	panel = &menu->light_panel;

	color_label_init(
		mlx, menu, &panel->color_label, (uint32_t[2]){g_pos[0], g_pos[1] + 30});
	button_init(mlx, &panel->color_label_button_r,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 50});
	panel->color_label_button_r.f = NULL;
	panel->color_label_button_r.min = 0.0f;
	panel->color_label_button_r.max = 255.0f;
	panel->color_label_button_r.step = 1.0f;
	button_init(mlx, &panel->color_label_button_g,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 70});
	panel->color_label_button_g.f = NULL;
	panel->color_label_button_g.min = 0.0f;
	panel->color_label_button_g.max = 255.0f;
	panel->color_label_button_g.step = 1.0f;
	button_init(mlx, &panel->color_label_button_b,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 90});
	panel->color_label_button_b.f = NULL;
	panel->color_label_button_b.min = 0.0f;
	panel->color_label_button_b.max = 255.0f;
	panel->color_label_button_b.step = 1.0f;
}

static void	_init_intensity_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_light_panel *const	panel = &menu->light_panel;

	float_label_init(&panel->intensity_label, "intensity: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 50});
	button_init(mlx, &panel->intensity_label_button,
		(int32_t[2]){g_pos[0] + 335, g_pos[1] + 50});
	panel->intensity_label_button.f = NULL;
	panel->intensity_label_button.min = 0.0f;
	panel->intensity_label_button.max = 1.0f;
	panel->intensity_label_button.step = 0.01f;
}

static void	_init_position_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_light_panel *const	panel = &menu->light_panel;

	panel->position_label = vec3_label_init(mlx, menu, "position:",
			(uint32_t[2]){g_pos[0], g_pos[1] + 120});
	button_init(mlx, &panel->position_label_button_x,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 140});
	panel->position_label_button_x.f = NULL;
	panel->position_label_button_x.min = -10000.0f;
	panel->position_label_button_x.max = 10000.0f;
	panel->position_label_button_x.step = 0.01f;
	button_init(mlx, &panel->position_label_button_y,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 160});
	panel->position_label_button_y.f = NULL;
	panel->position_label_button_y.min = -10000.0f;
	panel->position_label_button_y.max = 10000.0f;
	panel->position_label_button_y.step = 0.01f;
	button_init(mlx, &panel->position_label_button_z,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 180});
	panel->position_label_button_z.f = NULL;
	panel->position_label_button_z.min = -10000.0f;
	panel->position_label_button_z.max = 10000.0f;
	panel->position_label_button_z.step = 0.01f;
}
