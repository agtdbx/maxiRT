/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:54:10 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 13:13:37 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene_bonus.h"

static const uint32_t	g_pos[2] = {20, 310};

static void	object_title_init(
				mlx_t *mlx,
				t_menu *menu,
				t_object_panel *const panel);

void	object_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;

	panel->is_enabled = false;
	object_title_init(mlx, menu, panel);
	init_color_label(mlx, menu);
	init_opacity_label(mlx, menu);
	init_density_label(mlx, menu);
	init_reflection_label(mlx, menu);
	cone_panel_init(mlx, menu);
	cube_panel_init(mlx, menu);
	plane_panel_init(mlx, menu);
	sphere_panel_init(mlx, menu);
	cylinder_panel_init(mlx, menu);
}

static void	object_title_init(
			mlx_t *mlx,
			t_menu *menu,
			t_object_panel *const panel)
{
	panel->title = NULL;
	panel->cone_title = mlx_put_string(mlx, "-- Cone --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	panel->cone_title->enabled = false;
	panel->cube_title = mlx_put_string(mlx, "-- Cube --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	panel->cube_title->enabled = false;
	panel->plane_title = mlx_put_string(mlx, "-- Plane --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	panel->plane_title->enabled = false;
	panel->sphere_title = mlx_put_string(mlx, "-- Sphere --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	panel->sphere_title->enabled = false;
	panel->cylinder_title = mlx_put_string(mlx, "-- Cylinder --",
			menu->background->instances->x + g_pos[0], g_pos[1]);
	panel->cylinder_title->enabled = false;
}
