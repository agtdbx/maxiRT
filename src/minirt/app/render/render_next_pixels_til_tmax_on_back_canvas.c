/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_pixels_til_tmax_on_back_canvas.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <aderouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:56:46 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/23 13:29:43 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdbool.h>
#include <stdint.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene.h"
#include "minirt/app/canvas/canvas.h"
#include "minirt/app/utils/geometry/geometry.h"

static void	_render_one_pixel_on_back_canvas(
				t_scene const *scene,
				t_canvas const *canvas,
				int32_t const coords[2],
				bool show_spotlights);

int32_t	render_next_pixels_til_tmax_on_back_canvas(
			t_app *app,
			int32_t pixel_rendered)
{
	double			tmax;
	int32_t			pixel_coords[2];
	int32_t			new_pixel_rendered;

	new_pixel_rendered = 0;
	pixel_coords[0] = pixel_rendered % app->canvas.width;
	pixel_coords[1] = pixel_rendered / app->canvas.width;
	tmax = mlx_get_time() - app->mlx->delta_time + 0.15;
	while (pixel_coords[1] < app->canvas.height)
	{
		while (pixel_coords[0] < app->canvas.width)
		{
			_render_one_pixel_on_back_canvas(
				&app->scene, &app->canvas, pixel_coords, app->menu.is_visible);
			++new_pixel_rendered;
			if (mlx_get_time() > tmax)
			{
				return (new_pixel_rendered);
			}
			pixel_coords[0] += 1;
		}
		pixel_coords[1] += 1;
		pixel_coords[0] = 0;
	}
	return (new_pixel_rendered);
}

static void	_render_one_pixel_on_back_canvas(
				t_scene const *scene,
				t_canvas const *canvas,
				int32_t const coords[2],
				bool show_spotlights)
{
	int32_t	color;
	t_ray	casted_ray;

	casted_ray = create_ray_from_pixel_coords(scene->camera, canvas, coords);
	casted_ray.depth = 0;
	color = render_ray_from_camera(scene, &casted_ray, show_spotlights);
	mlx_put_pixel(canvas->back, coords[0], coords[1], color);
}
