/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window_resizing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:47:45 by tdubois           #+#    #+#             */
/*   Updated: 2024/12/26 14:46:06 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"
#include "minirt/app/app.h"
#include "minirt/app/app_config.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/menu/menu.h"
#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/drawings/drawings.h"

#define FRONT_CANVAS 0
#define BACK_CANVAS 1
#define RECORD_ICON_X_POS 20
#define Y 1
#define RED_COLOR 0xFF0000FF

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
			t_canvas *canvas,
			t_sync *sync)
{
	int32_t const	width = mlx->width - menu->is_visible * g_menu_width;
	int32_t const	height = mlx->height;
	static int		coords_record_icon[2] = {RECORD_ICON_X_POS, 0};

	if (canvas->width != width || canvas->height != height)
	{
		coords_record_icon[Y] =  height - 40;
		mlx_resize_image(canvas->record_icon, width, height);
		img_fill(canvas->record_icon, 0x00000000);
		img_draw_square(canvas->record_icon, coords_record_icon, 20, RED_COLOR);
		pthread_mutex_lock(&sync->canvas_mut[FRONT_CANVAS]);
		mlx_resize_image(canvas->front, width, height);
		sync->reset_render = 1;
		pthread_mutex_unlock(&sync->canvas_mut[FRONT_CANVAS]);
		pthread_mutex_lock(&sync->canvas_mut[BACK_CANVAS]);
		mlx_resize_image(canvas->back, width, height);
		pthread_mutex_unlock(&sync->canvas_mut[BACK_CANVAS]);
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
