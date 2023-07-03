/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_label_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:38:09 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 16:06:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt/app/menu/menu.h"

#include <stdint.h>

void	color_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_color_label *label,
			uint32_t const pos[2])
{
	label->title = "color:";
	label->x = pos[0];
	label->y = pos[1];
	label->img_title = mlx_put_string(
		mlx, label->title,
		menu->background->instances->x + pos[0], pos[1]);
	int_label_init(
		&label->label_r, "| r: ", (uint32_t[2]){pos[0], pos[1] + 20});
	int_label_init(
		&label->label_g, "| g: ", (uint32_t[2]){pos[0], pos[1] + 40});
	int_label_init(
		&label->label_b, "| b: ", (uint32_t[2]){pos[0], pos[1] + 60});
}
