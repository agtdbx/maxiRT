/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_label_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:55:15 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:33:51 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stddef.h>

#include "MLX42/MLX42.h"

void	color_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_color_label *label)
{
	int_label_draw(mlx, menu, &label->label_r);
	int_label_draw(mlx, menu, &label->label_g);
	int_label_draw(mlx, menu, &label->label_b);
	if (label->img_title == NULL)
		return ;
	label->img_title->instances->x = menu->background->instances->x + label->x;
	label->img_title->instances->y = menu->background->instances->y + label->y;
}
