/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_update_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:01:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:31:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

#include "minirt/app/app_config.h"

/**
 * sets menu's position based on window size
 * @param[in] mlx
 * @param[out] menu
 */
void	menu_update_position(
			mlx_t const *mlx,
			t_menu *menu)
{
	menu->background->instances->x = mlx->width - g_menu_width;
}
