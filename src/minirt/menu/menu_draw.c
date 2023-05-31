/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:48:44 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 17:55:20 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"
#include <minirt/menu/menu.h>

#include <MLX42/MLX42.h>

void	menu_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	if (!menu->is_visible)
		return ;
	camera_label_draw(mlx, menu);
}
