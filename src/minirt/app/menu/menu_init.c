/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:54:53 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/07 15:51:17 by tdubois          ###   ########.fr       */
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

static t_error	_menu_init_background(
					mlx_t *mlx,
					t_menu *menu);

t_error	menu_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{
	if (_menu_init_background(mlx, menu) == FAILURE)
		return (FAILURE);
	menu_update_position(mlx, menu);
	camera_label_init(mlx, menu, scene);
	ambient_label_init(mlx, menu, scene);
	object_panel_init(mlx, menu);
	menu_hide(menu);
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
