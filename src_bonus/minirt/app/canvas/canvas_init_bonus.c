/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/09 16:00:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/canvas/canvas_bonus.h>

#include <stdbool.h>
#include <stddef.h>

#include "MLX42/MLX42.h"

t_error	canvas_init(
			mlx_t *mlx,
			t_canvas *canvas)
{
	canvas->front = mlx_new_image(mlx, mlx->width, mlx->height);
	if (canvas->front == NULL)
		return (FAILURE);
	if (mlx_image_to_window(mlx, canvas->front, 0, 0) == -1)
		return (FAILURE);
	canvas->back = mlx_new_image(mlx, mlx->width, mlx->height);
	if (canvas->back == NULL)
		return (FAILURE);
	canvas->back->enabled = false;
	if (mlx_image_to_window(mlx, canvas->back, 0, 0) == -1)
		return (FAILURE);
	canvas->width = 0;
	canvas->height = 0;
	return (SUCCESS);
}
