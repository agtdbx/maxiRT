/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_clicks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:25:41 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/20 16:41:06 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>
#include <stdbool.h>

#include "MLX42/MLX42.h"

#include "minirt/app/menu/menu.h"
#include "minirt/debug/debug.h"//TODO

bool	handle_mouse_clicks(
			mlx_t *mlx,
			t_menu *menu,
			t_scene *scene,
			t_canvas *canvas)
{
	int32_t			pix[2];
	static double	no_clicks_until = 0;

	if (!menu->is_visible
		|| !mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_get_time() < no_clicks_until)
		return (false);
	no_clicks_until = mlx_get_time() + 0.25;
	mlx_get_mouse_pos(mlx, &pix[0], &pix[1]);
	if (menu->background->instances->x < pix[0])
		return (true);
	DEBUG_ON(); //TODO for debugging
	(void)render_one_pixel(scene, canvas, pix, true);
	DEBUG_OFF();
	return (false);
}
