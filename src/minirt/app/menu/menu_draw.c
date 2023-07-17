/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:48:44 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 17:18:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"

bool	menu_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_canvas *canvas,
			t_scene const *scene)
{
	bool	should_redraw;

	if (!menu->is_visible)
		return (false);
	should_redraw = false;
	should_redraw |= camera_label_draw(mlx, menu, canvas, scene);
	should_redraw |= ambient_label_draw(mlx, menu);
	should_redraw |= object_panel_draw(mlx, menu);
	should_redraw |= light_panel_draw(mlx, menu);
	return (should_redraw);
}
