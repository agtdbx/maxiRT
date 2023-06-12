/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window_resizing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:47:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/12 14:15:40 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/app_config.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/menu/menu.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/drawings/drawings.h"

/**
 * Resize canvas if smaller than window, 
 * then update camera's focal accordingly
 * and reposition menu
 *
 * @param[in] app the app handle
 * @param[out] canvas The canvas to be resized
 * @returns Wether scene should be re-rendered
 */
bool	handle_window_resizing(
			mlx_t *mlx,
			t_menu *menu,
			t_scene *scene,
			t_canvas *canvas)
{
	int32_t const	width = mlx->width - menu->is_visible * g_menu_width;
	int32_t const	height = mlx->height;

	if (canvas->width != width || canvas->height != height)
	{
		mlx_resize_image(canvas->front, width, height);
		mlx_resize_image(canvas->back, width, height);
		mlx_resize_image(menu->background, menu->background->width, height);
		canvas->width = width;
		canvas->height = height;
		canvas->width_div_2 = width / 2.0f;
		canvas->height_div_2 = height / 2.0f;
		camera_compute_constants(canvas, scene->camera);
		menu_update_position(mlx, menu);
		background_draw(menu);
		return (true);
	}
	return (false);
}
