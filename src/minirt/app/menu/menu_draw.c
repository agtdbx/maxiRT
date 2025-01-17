/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:48:44 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/17 23:31:01 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"

static bool	_color_filter_label_draw(
			mlx_t *mlx,
			t_menu *menu);

bool	menu_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_canvas *canvas,
			pthread_rwlock_t *scene_mut,
			t_scene const *scene)
{
	bool	should_redraw;

	if (!menu->is_visible)
		return (false);
	should_redraw = false;
	should_redraw |= camera_label_draw(mlx, menu, canvas, scene);
	should_redraw |= _color_filter_label_draw(mlx, menu);
	should_redraw |= ambient_label_draw(mlx, menu);
	pthread_rwlock_wrlock(scene_mut);
	should_redraw |= object_panel_draw(mlx, menu);
	pthread_rwlock_unlock(scene_mut);
	should_redraw |= light_panel_draw(mlx, menu);
	return (should_redraw);
}


static bool	_color_filter_label_draw(
			mlx_t *mlx,
			t_menu *menu)
{
	bool	should_redraw;

	menu->camera_label_title->instances->x = \
		menu->background->instances->x + 20;
	vec3_label_draw(mlx, menu, &menu->color_filter_label);
	should_redraw = false;
	should_redraw |= button_draw(mlx, menu, &menu->color_filter_button_r);
	should_redraw |= button_draw(mlx, menu, &menu->color_filter_button_g);
	should_redraw |= button_draw(mlx, menu, &menu->color_filter_button_b);
	return (should_redraw);
}
