/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:42 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/03 17:55:03 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/canvas/canvas.h>
#include <minirt/app/app.h>
#include <MLX42/MLX42.h>
#include <libft/libft.h>

t_error	canvas_init(t_app *app)
{
	app->canvas.front =
		mlx_new_image(app->mlx, app->mlx->width, app->mlx->height);
	if (app->canvas.front == NULL)
		return (FAILURE);
	app->canvas.back =
		mlx_new_image(app->mlx, app->mlx->width, app->mlx->height);
	if (app->canvas.back == NULL)
		return (FAILURE);
	return (SUCCESS);
}
