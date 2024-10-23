/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_panel_draw.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguste <auguste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:16:20 by tdubois           #+#    #+#             */
/*   Updated: 2024/04/21 15:47:57 by auguste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"
#include "minirt/app/scene/scene.h"

bool	sphere_panel_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	vec3_label_draw(mlx, menu, &menu->object_panel.sphere_label.position_label);
	float_label_draw(mlx, menu,
		&menu->object_panel.sphere_label.diameter_label);
	should_redraw = false;
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.sphere_label.position_label_button_x);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.sphere_label.position_label_button_y);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.sphere_label.position_label_button_z);
	should_redraw |= button_draw(mlx, menu,
			&menu->object_panel.sphere_label.diameter_label_button);
	if (should_redraw)
	{
		sphere_compute_constants(
			(t_sphere *)menu->object_panel.object_ptr,
			menu->object_panel.object_bbox);
		compute_scene_binary_tree(menu->scene);
	}
	return (should_redraw);
}
