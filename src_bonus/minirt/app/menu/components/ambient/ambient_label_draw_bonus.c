/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:47:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 13:16:42 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"

#include "minirt/app/utils/color/color_bonus.h"

bool	ambient_label_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	menu->ambient_label_title->instances->x = \
		menu->background->instances->x + 20;
	color_label_draw(mlx, menu, &menu->ambient_color_label);
	float_label_draw(mlx, menu, &menu->ambient_ratio_label);
	should_redraw = false;
	should_redraw |= button_draw(mlx, menu, &menu->ambient_ratio_button);
	should_redraw |= button_draw(mlx, menu, &menu->ambient_color_button_r);
	should_redraw |= button_draw(mlx, menu, &menu->ambient_color_button_g);
	should_redraw |= button_draw(mlx, menu, &menu->ambient_color_button_b);
	return (should_redraw);
}
