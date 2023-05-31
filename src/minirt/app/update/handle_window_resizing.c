/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window_resizing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:47:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/31 20:07:27 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/canvas/canvas.h>
#include <minirt/menu/menu.h>
#include <minirt/scene/scene.h>
#include <minirt/utils/drawings.h>

#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Resize canvas if smaller than window, 
 * then update camera's focal accordingly
 * and reposition menu
 *
 * @param[in] mlx The mlx handle
 * @param[out] canvas The canvas to be resized
 * @returns Wether scene should be re-rendered
 */
bool	handle_window_resizing(
			mlx_t const *mlx,
			t_canvas *canvas,
			t_camera *camera,
			t_menu *menu)
{
	int32_t const viewport_width = mlx->width - menu->is_visible * MENU_WIDTH;
	int32_t const viewport_height = mlx->height;

	if (canvas->width != viewport_width || canvas->height != viewport_height)
	{
		if (canvas->width < mlx->width || canvas->height < mlx->height)
		{
			mlx_resize_image(canvas->front, mlx->width, mlx->height);
			mlx_resize_image(canvas->back, mlx->width, mlx->height);
			img_fill(menu->background, MENU_BACKGROUND_COLOR);
		}
		canvas->width = viewport_width;
		canvas->height = viewport_height;
		canvas->width_div_2 = viewport_width / 2.0f;
		canvas->height_div_2 = viewport_height / 2.0f;
		camera_compute_constants(canvas, camera);
		menu_update_position(mlx, menu);
		return (true);
	}
	return (false);
}
