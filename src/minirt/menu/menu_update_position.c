/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_update_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:01:51 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/17 15:04:47 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>

/**
 * sets menu's position based on window size
 * @param[in] mlx
 * @param[out] menu
 */
void	menu_update_position(
			mlx_t const *mlx,
			t_menu *menu)
{
	menu->background->instances->x = mlx->width - MENU_WIDTH;
}
