/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:47:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 15:59:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

#include "minirt/app/utils/color/color.h"

void	ambient_label_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	menu->ambient_label_title->instances->x = \
		menu->background->instances->x + 20;
	color_label_draw(mlx, menu, &menu->ambient_color_label);
	float_label_draw(mlx, menu, &menu->ambient_ratio_label);
}
