/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_clicks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:25:41 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/18 13:12:34 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/app.h"

#include <stdint.h>
#include <stdbool.h>

#include "MLX42/MLX42.h"

#include "minirt/app/menu/menu.h"
#include "minirt/app/scene/scene.h"
#include "minirt/debug/debug.h"//TODO

static bool	_has_clicked_on_canvas(
				t_canvas const *canvas,
				int32_t	const coords[2]);
static void	_handle_clicks_on_canvas(
				t_menu *menu,
				t_scene *scene,
				t_canvas const *canvas,
				int32_t const pix[2]);

void	handle_mouse_clicks(
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
		return ;
	no_clicks_until = mlx_get_time() + 0.25;
	mlx_get_mouse_pos(mlx, &pix[0], &pix[1]);

	if (_has_clicked_on_canvas(canvas, pix))
	{
		DEBUG_ON(); //TODO for debugging
		(void)render_one_pixel(scene, canvas, pix, true);
		DEBUG_OFF();
		_handle_clicks_on_canvas(menu, scene, canvas, pix);
		return ;
	}
}

static bool	_has_clicked_on_canvas(
				t_canvas const *canvas,
				int32_t	const coords[2])
{
	if (0 < coords[0] && coords[0] < canvas->width)
	{
		if (0 < coords[1] && coords[1] < canvas->height)
		{
			return (true);
		}
	}
	return (false);
}

static void	_handle_clicks_on_canvas(
				t_menu *menu,
				t_scene *scene,
				t_canvas const *canvas,
				int32_t const pix[2])
{
		t_ray				ray; 
		t_intersect_info	info;
		t_object			*object;
		t_light				*light;
		
		(void) menu;

		ray = create_ray_from_pixel_coords(scene->camera, canvas, pix);
		object = fetch_closest_intersection(&ray, scene->objects, &info);
		light = fetch_closer_spotlight(&ray, scene->spotlights, &info);
		if (light != NULL)
		{
			light_panel_register(menu, light);
			return ;
		}
		if (object != NULL)
		{
			object_panel_register(menu, object);
		}
}
