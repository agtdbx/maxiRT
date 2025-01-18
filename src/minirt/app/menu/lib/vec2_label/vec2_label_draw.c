/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_label_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:54:49 by gugus             #+#    #+#             */
/*   Updated: 2025/01/18 19:56:21 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stddef.h>

#include "MLX42/MLX42.h"

void	vec2_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_vec2_label *label)
{
	float_label_draw(mlx, menu, &label->label_x);
	float_label_draw(mlx, menu, &label->label_y);
	if (label->img_title == NULL)
		return ;
	label->img_title->instances->x = menu->background->instances->x + label->x;
	label->img_title->instances->y = menu->background->instances->y + label->y;
}
