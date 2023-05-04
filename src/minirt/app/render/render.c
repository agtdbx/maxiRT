/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 13:37:48 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/app/app.h>

#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdint.h>

void	render(
			t_app *app,
			bool should_render)
{
	static bool		is_rendering = true;
	static int32_t	pixel_rendered = 0;
	double			tmax;

	if (should_render)
	{
		is_rendering = true;
		pixel_rendered = 0;
		// fast_render()
		return ;
	}
	if (!is_rendering)
		return ;
	tmax = mlx_get_time() - app->mlx->delta_time + 0.25;
	while (pixel_rendered < app->mlx->width * app->mlx->height)
	{
		//render_one_pixel
		++pixel_rendered;
		if (mlx_get_time() > tmax)
			return;
	}
	is_rendering = false;
	// canvas_swap(&app->canvas);
}
