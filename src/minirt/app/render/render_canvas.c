/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:57 by tdubois           #+#    #+#             */
/*   Updated: 2023/06/21 15:17:13 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"
#include "libft/libft.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/utils/drawings/drawings.h"
#include "minirt/app/utils/geometry/geometry.h"

static void	_print_rendering_progress(
				mlx_t *mlx,
				bool is_rendering,
				int32_t	pixel_rendered);
static void	_update_ppr(
				double delta_time,
				int32_t *ppr);
static bool	_is_under_10_fps(
				double delta_time);
static bool	_is_over_25_fps(
				double delta_time);

void	render_canvas(
			t_app *app,
			bool should_render_fast)
{
	static int32_t	pixel_rendered = 0;
	static int32_t	pixel_per_ray = 16;
	static bool		is_rendering = false;

	if (should_render_fast)
	{
		if (is_rendering)
			_update_ppr(app->mlx->delta_time, &pixel_per_ray);
		render_fast_on_front_canvas(app, pixel_per_ray);
		is_rendering = true;
		pixel_rendered = 0;
		return ;
	}
	_print_rendering_progress(app->mlx, is_rendering, pixel_rendered);
	if (is_rendering)
	{
		pixel_rendered += render_next_pixels_til_tmax_on_back_canvas(
				app, pixel_rendered);
		if (pixel_rendered == app->canvas.width * app->canvas.height)
		{
			canvas_swap(&app->canvas);
			is_rendering = false;
		}
	}
}

static void	_print_rendering_progress(
				mlx_t *mlx,
				bool is_rendering,
				int32_t	pixel_rendered)
{
	static mlx_image_t	*img = NULL;
	float				progress_rate;
	char				str[30];
	size_t				len;

	if (img != NULL)
	{
		mlx_delete_image(mlx, img);
		img = NULL;
	}
	if (!is_rendering)
		return ;
	progress_rate = pixel_rendered;
	progress_rate *= 100.0f / (mlx->width * mlx->height);
	len = ft_sitoa(progress_rate, str, sizeof(str));
	ft_strlcpy(str + len, " %", sizeof(str) - len);
	img = mlx_put_string(mlx, str, 10, 10);
	mlx_set_instance_depth(img->instances, 3);
}

/**
 * auto update ppr according to last dt
 * @param[in] mlx
 * @param[out] ppr
 */
static inline void	_update_ppr(
						double delta_time,
						int32_t *ppr)
{
	if (_is_under_10_fps(delta_time) && *ppr < 25)
	{
		++(*ppr);
	}
	if (_is_over_25_fps(delta_time) && 1 < *ppr)
	{
		--(*ppr);
	}
}

static bool	_is_under_10_fps(
				double delta_time)
{
	return (0.1 < delta_time);
}

static bool	_is_over_25_fps(
				double delta_time)
{
	return (delta_time < 0.04);
}
