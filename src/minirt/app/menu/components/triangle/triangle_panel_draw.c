/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_panel_draw.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:48:08 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

bool	triangle_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	should_redraw = false;
	vec3_label_draw(mlx, menu, &menu->object_panel.triangle_panel.position_p1_label);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p1_label_button_x);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p1_label_button_y);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p1_label_button_z);
	vec3_label_draw(mlx, menu, &menu->object_panel.triangle_panel.position_p2_label);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p2_label_button_x);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p2_label_button_y);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p2_label_button_z);
	vec3_label_draw(mlx, menu, &menu->object_panel.triangle_panel.position_p3_label);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p3_label_button_x);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p3_label_button_y);
	should_redraw |= button_draw(
			mlx, menu, &menu->object_panel.triangle_panel.position_p3_label_button_z);
	if (should_redraw)
	{
		triangle_compute_constants(
			(t_triangle *)menu->object_panel.object_ptr,
			menu->object_panel.object_bbox);
		compute_scene_binary_tree(menu->scene);
	}
	return (should_redraw);
}
