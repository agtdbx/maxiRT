/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:54:53 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:48:04 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stddef.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/app_config.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/drawings/drawings.h"

static const uint32_t	g_pos[2] = {20, 125};

static t_error	_menu_init_background(
					mlx_t *mlx,
					t_menu *menu);
static void		_color_filter_label_init(
					mlx_t *mlx,
					t_menu *menu,
					t_scene *scene);

t_error	menu_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene *scene)
{
	if (_menu_init_background(mlx, menu) == FAILURE)
		return (FAILURE);
	menu_update_position(mlx, menu);
	camera_label_init(mlx, menu, scene);
	_color_filter_label_init(mlx, menu, scene);
	ambient_label_init(mlx, menu, scene);
	object_panel_init(mlx, menu);
	light_panel_init(mlx, menu);
	menu_hide(menu);
	menu->scene = scene;
	return (SUCCESS);
}

static t_error	_menu_init_background(
					mlx_t *mlx,
					t_menu *menu)
{
	menu->is_visible = true;
	menu->background = mlx_new_image(mlx, g_menu_width, mlx->height);
	if (menu->background == NULL)
		return (FAILURE);
	background_draw(menu);
	if (mlx_image_to_window(mlx, menu->background, 0, 0) == -1)
		return (FAILURE);
	mlx_set_instance_depth(&menu->background->instances[0], 2);
	return (SUCCESS);
}


static void	_color_filter_label_init(
				mlx_t *mlx,
				t_menu *menu,
				t_scene *scene)
{
	menu->color_filter_label = vec3_label_init(mlx, menu, "color filter: ",
									(uint32_t[2]){g_pos[0], g_pos[1] + 30});
	menu->color_filter_label.label_x.f = &scene->color_filter.x;
	menu->color_filter_label.label_y.f = &scene->color_filter.y;
	menu->color_filter_label.label_z.f = &scene->color_filter.z;
	button_init(mlx, &menu->color_filter_button_r,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 50});
	menu->color_filter_button_r.f = &scene->color_filter.x;
	menu->color_filter_button_r.min = 0.0f;
	menu->color_filter_button_r.max = 1.0f;
	menu->color_filter_button_r.step = 0.01f;
	button_init(mlx, &menu->color_filter_button_g,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 70});
	menu->color_filter_button_g.f = &scene->color_filter.y;
	menu->color_filter_button_g.min = 0.0f;
	menu->color_filter_button_g.max = 1.0f;
	menu->color_filter_button_g.step = 0.01f;
	button_init(mlx, &menu->color_filter_button_b,
		(int32_t[2]){g_pos[0] + 100, g_pos[1] + 90});
	menu->color_filter_button_b.f = &scene->color_filter.z;
	menu->color_filter_button_b.min = 0.0f;
	menu->color_filter_button_b.max = 1.0f;
	menu->color_filter_button_b.step = 0.01f;
}

