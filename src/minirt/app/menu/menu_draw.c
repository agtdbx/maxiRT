/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:48:44 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:42:30 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

void	menu_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	static double	date_of_next_redraw = 0.0;

	if (!menu->is_visible || mlx_get_time() < date_of_next_redraw)
		return ;
	date_of_next_redraw = mlx_get_time() + 0.25;
	camera_label_draw(mlx, menu);
	ambient_label_draw(mlx, menu);
}
