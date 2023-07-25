/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_panel_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/19 21:02:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene_bonus.h"

bool	plane_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu, &menu->object_panel.plane_panel.position_label);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.plane_panel.position_label_button_x);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.plane_panel.position_label_button_y);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.plane_panel.position_label_button_z);
	vec3_label_draw(mlx, menu, &menu->object_panel.plane_panel.direction_label);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.plane_panel.direction_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.plane_panel.direction_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.plane_panel.direction_label_button_z);
	if (should_redraw)
		plane_compute_constants((t_plane *)menu->object_panel.object_ptr);
	return (should_redraw);
}
