/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:35:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 20:58:56 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene_bonus.h"

#include <stdint.h>

static void	_init_color_label(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene);

static void	_init_float_label(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene);

static const uint32_t	g_pos[2] = {20, 170};

void	ambient_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{
	menu->ambient_label_title = \
		mlx_put_string(mlx, "ambient light:", g_pos[0], g_pos[1]);
	_init_color_label(mlx, menu, scene);
	_init_float_label(mlx, menu, scene);
}

static void	_init_color_label(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene)
{
	color_label_init(mlx, menu, &menu->ambient_color_label,
		(uint32_t[2]){g_pos[0], g_pos[1] + 30});
	menu->ambient_color_label.label_r.f = &scene->ambient_lightning->color.r;
	menu->ambient_color_label.label_g.f = &scene->ambient_lightning->color.g;
	menu->ambient_color_label.label_b.f = &scene->ambient_lightning->color.b;
	button_init(mlx, &menu->ambient_color_button_r,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 50});
	menu->ambient_color_button_r.f = &scene->ambient_lightning->color.r;
	menu->ambient_color_button_r.min = 0.0f;
	menu->ambient_color_button_r.max = 255.0f;
	menu->ambient_color_button_r.step = 1.0f;
	button_init(mlx, &menu->ambient_color_button_g,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 70});
	menu->ambient_color_button_g.f = &scene->ambient_lightning->color.g;
	menu->ambient_color_button_g.min = 0.0f;
	menu->ambient_color_button_g.max = 255.0f;
	menu->ambient_color_button_g.step = 1.0f;
	button_init(mlx, &menu->ambient_color_button_b,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 90});
	menu->ambient_color_button_b.f = &scene->ambient_lightning->color.b;
	menu->ambient_color_button_b.min = 0.0f;
	menu->ambient_color_button_b.max = 255.0f;
	menu->ambient_color_button_b.step = 1.0f;
}

static void	_init_float_label(
				mlx_t *mlx,
				t_menu *menu,
				t_scene const *scene)
{
	float_label_init(&menu->ambient_ratio_label, "ratio: ",
		(uint32_t[2]){g_pos[0] + 180, g_pos[1] + 30});
	menu->ambient_ratio_label.f = &scene->ambient_lightning->brightness;
	button_init(mlx, &menu->ambient_ratio_button,
		(int32_t[2]){g_pos[0] + 330, g_pos[1] + 30});
	menu->ambient_ratio_button.f = &scene->ambient_lightning->brightness;
	menu->ambient_ratio_button.min = 0.0f;
	menu->ambient_ratio_button.max = 1.0f;
	menu->ambient_ratio_button.step = 0.01f;
}
