/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:42 by tdubois           #+#    #+#             */
/*   Updated: 2025/01/10 01:14:18 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/canvas/canvas.h>

#include <stdbool.h>
#include <stddef.h>

#include "MLX42/MLX42.h"

t_error	canvas_init(
			mlx_t *mlx,
			t_canvas *canvas)
{
	canvas->render_icon = mlx_new_image(mlx, mlx->width, mlx->height);
	if (mlx_image_to_window(mlx, canvas->render_icon, 0, 0) == -1)
		return (FAILURE);
	canvas->render_icon->instances->z = -1;
	canvas->front = mlx_new_image(mlx, mlx->width, mlx->height);
	if (canvas->front == NULL)
		return (FAILURE);
	if (mlx_image_to_window(mlx, canvas->front, 0, 0) == -1)
		return (FAILURE);
	canvas->front->instances->z = 0;
	canvas->back = mlx_new_image(mlx, mlx->width, mlx->height);
	if (canvas->back == NULL)
		return (FAILURE);
	canvas->back->enabled = false;
	if (mlx_image_to_window(mlx, canvas->back, 0, 0) == -1)
		return (FAILURE);
	canvas->back->instances->z = 0;
	canvas->width = 0;
	canvas->height = 0;
	return (SUCCESS);
}
