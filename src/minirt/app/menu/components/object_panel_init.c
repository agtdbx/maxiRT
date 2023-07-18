/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:26 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 14:17:15 by tdubois          ###   ########.fr       */
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
static void	_init_opacity_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_density_label(
				mlx_t *mlx,
				t_menu *menu);
static void	_init_reflection_label(
				mlx_t *mlx,
				t_menu *menu);

void	object_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

	panel->is_enabled = false;
	panel->title = NULL;
	panel->sphere_title = mlx_put_string(mlx, "-- Sphere --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	_init_color_label(mlx, menu);
	_init_opacity_label(mlx, menu);
	_init_density_label(mlx, menu);
	_init_reflection_label(mlx, menu);
	sphere_panel_init(mlx, menu);
}

static void	_init_color_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

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

static void	_init_opacity_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

	float_label_init(&panel->opacity_label, "opacity: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 50});
	button_init(mlx, &panel->opacity_label_button,
		(int32_t[2]){g_pos[0] + 335, g_pos[1] + 50});
	panel->opacity_label_button.f = NULL;
	panel->opacity_label_button.min = 0.0f;
	panel->opacity_label_button.max = 1.0f;
	panel->opacity_label_button.step = 0.01f;
}

static void	_init_density_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

	float_label_init(&panel->density_label, "density: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 70});
	button_init(mlx, &panel->density_label_button,
		(int32_t[2]){g_pos[0] + 335, g_pos[1] + 70});
	panel->density_label_button.f = NULL;
	panel->density_label_button.min = 0.0f;
	panel->density_label_button.max = 1.0f;
	panel->density_label_button.step = 0.01f;
}

static void	_init_reflection_label(
				mlx_t *mlx,
				t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

	float_label_init(&panel->reflection_label, "reflection: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 90});
	button_init(mlx, &panel->reflection_label_button,
		(int32_t[2]){g_pos[0] + 335, g_pos[1] + 90});
	panel->reflection_label_button.f = NULL;
	panel->reflection_label_button.min = 0.0f;
	panel->reflection_label_button.max = 1.0f;
	panel->reflection_label_button.step = 0.01f;
}

