/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_label_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:32:22 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 14:38:35 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stddef.h>

#include "MLX42/MLX42.h"

void	vec3_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_vec3_label *label)
{
	float_label_draw(mlx, menu, &label->label_x);
	float_label_draw(mlx, menu, &label->label_y);
	float_label_draw(mlx, menu, &label->label_z);
	if (label->img_title == NULL)
		return ;
	label->img_title->instances->x = menu->background->instances->x + label->x;
	label->img_title->instances->y = menu->background->instances->y + label->y;
}
