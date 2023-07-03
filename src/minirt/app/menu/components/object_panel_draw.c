/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:48:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/03 12:20:44 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

void	object_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	if (!menu->object_panel.is_enabled)
		return ;
	if (menu->object_panel.title != NULL)
	{
		menu->object_panel.title->instances->x = \
			menu->background->instances->x + 20;
	}
	color_label_draw(mlx, menu, &menu->object_panel.color_label);
	float_label_draw(mlx, menu, &menu->object_panel.opacity_label);
	float_label_draw(mlx, menu, &menu->object_panel.density_label);
	float_label_draw(mlx, menu, &menu->object_panel.reflection_label);
	if (menu->object_panel.object_type == OBJ_SPHERE)
		sphere_panel_draw(mlx, menu);
}
