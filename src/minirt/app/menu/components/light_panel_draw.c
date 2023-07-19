/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:48:00 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 21:12:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

bool	light_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	if (!menu->light_panel.is_enabled)
		return (false);
	if (menu->light_panel.title != NULL)
	{
		menu->light_panel.title->instances->x = \
			menu->background->instances->x + 20;
	}
	should_redraw = false;
	color_label_draw(mlx, menu, &menu->light_panel.color_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.color_label_button_r);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.color_label_button_g);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.color_label_button_b);
	float_label_draw(mlx, menu, &menu->light_panel.intensity_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.intensity_label_button);
	vec3_label_draw(mlx, menu, &menu->light_panel.position_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.position_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.position_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->light_panel.position_label_button_z);
	return (should_redraw);
}
