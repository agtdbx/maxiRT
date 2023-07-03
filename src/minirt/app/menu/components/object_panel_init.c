/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:26 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 16:18:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"

void	object_panel_init(
			mlx_t *mlx,
			t_menu *menu)
{
	t_object_panel *const	panel = &menu->object_panel;
	uint32_t const			pos[2] = {20, 310};

	panel->is_enabled = false;
	panel->title = NULL;
	panel->sphere_title = mlx_put_string(mlx, "-- Sphere --", 
			menu->background->instances->x + pos[0], pos[1]);
	color_label_init(
		mlx, menu, &panel->color_label, (uint32_t[2]){pos[0], pos[1] + 30});
	float_label_init(&panel->opacity_label, "opacity: ",
		(uint32_t[2]){pos[0] + 180, pos[1] + 50});
	float_label_init(&panel->density_label, "density: ",
		(uint32_t[2]){pos[0] + 180, pos[1] + 70});
	float_label_init(&panel->reflection_label, "reflection: ",
		(uint32_t[2]){pos[0] + 180, pos[1] + 90});
	sphere_panel_init(mlx, menu);
}
