/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_canvas_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:47:45 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/16 15:46:18 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <minirt/canvas/canvas.h>
#include <MLX42/MLX42.h>
#include <stdbool.h>

/**
 * Resize canvas if smaller than window and update camera's focal accordingly
 *
 * @param[in] mlx The mlx handle
 * @param[out] canvas The canvas to be resized
 * @returns Wether scene should be re-rendered
 */
bool	update_canvas_size(
			mlx_t const *mlx,
			t_canvas *canvas,
			t_camera *camera)
{
	if (canvas->width != mlx->width || canvas->height != mlx->height)
	{
		if (canvas->width < mlx->width || canvas->height < mlx->height)
		{
			mlx_resize_image(canvas->front, mlx->width, mlx->height);
			mlx_resize_image(canvas->back, mlx->width, mlx->height);
		}
		canvas->width = mlx->width;
		canvas->height = mlx->height;
		canvas->width_div_2 = mlx->width / 2.0f;
		canvas->height_div_2 = mlx->height / 2.0f;
		camera_compute_constants(mlx, camera);
		return (true);
	}
	return (false);
}
