/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_canvas_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:47:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/15 22:54:01 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/canvas/canvas.h>
#include <MLX42/MLX42.h>

/**
 * Resize canvas if smaller than window
 * @param[in] mlx The mlx handle
 * @param[out] canvas The canvas to be resized
 * @returns Wether scene should be re-rendered
 */
bool	update_canvas_size(
			mlx_t const *mlx,
			t_canvas *canvas)
{
	if (canvas->front->width < (uint32_t) mlx->width
		|| canvas->front->height < (uint32_t) mlx->height)
	{
		mlx_resize_image(canvas->front, mlx->width, mlx->height);
		mlx_resize_image(canvas->back, mlx->width, mlx->height);
		return (true);
	}
	return (false);
}
