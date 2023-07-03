/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_label_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:35:33 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 16:15:52 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"
#include <stdint.h>

void	ambient_label_init(
			mlx_t *mlx,
			t_menu *menu,
			t_scene const *scene)
{
	uint32_t const pos[2] = {20, 170};

	menu->ambient_label_title = mlx_put_string(mlx, "ambient light:", pos[0], pos[1]);
	color_label_init(mlx, menu, &menu->ambient_color_label,
		(uint32_t[2]){pos[0], pos[1] + 30});
	menu->ambient_color_label.label_r.f = &scene->ambient_lightning->color.r;
	menu->ambient_color_label.label_g.f = &scene->ambient_lightning->color.g;
	menu->ambient_color_label.label_b.f = &scene->ambient_lightning->color.b;
	float_label_init(&menu->ambient_ratio_label, "ratio: ",
		(uint32_t[2]){pos[0] + 180, pos[1] + 30});
	menu->ambient_ratio_label.f = &scene->ambient_lightning->brightness;
}
