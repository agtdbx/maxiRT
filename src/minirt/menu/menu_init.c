/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:54:53 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 20:05:52 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <minirt/scene/scene.h>
#include <minirt/utils/drawings.h>

#include <MLX42/MLX42.h>
#include <libft/libft.h>
#include <stdbool.h>

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
	// menu_toggle(menu);
	menu_show(menu);
	return (SUCCESS);
}

static t_error	_menu_init_background(
					mlx_t *mlx,
					t_menu *menu)
{
	menu->is_visible = true;
	menu->background = mlx_new_image(mlx, MENU_WIDTH, mlx->height);
	if (menu->background == NULL)
		return (FAILURE);
	img_fill(menu->background, MENU_BACKGROUND_COLOR);
	if (mlx_image_to_window(mlx, menu->background, 0, 0) == -1)
		return (FAILURE);
	mlx_set_instance_depth(&menu->background->instances[0], 2);
	return (SUCCESS);
}
