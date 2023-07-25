/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_label_draw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by tdubois           #+#    #+#             */
/*   Updated: 2023/07/17 12:06:32 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/app/menu/menu_bonus.h"

#include <stdbool.h>

#include "MLX42/MLX42.h"

#include "minirt/app/scene/scene_bonus.h"
#include "minirt/app/utils/geometry/geometry_bonus.h"

bool	camera_label_draw(
			mlx_t *mlx,
			t_menu *menu,
			t_canvas *canvas,
			t_scene const *scene)
{
	menu->camera_label_title->instances->x = \
		menu->background->instances->x + 20;
	vec3_label_draw(mlx, menu, &menu->camera_dir_label);
	vec3_label_draw(mlx, menu, &menu->camera_pos_label);
	float_label_draw(mlx, menu, &menu->camera_fov_label);
	if (button_draw(mlx, menu, &menu->camera_fov_button))
	{
		camera_compute_constants(canvas, scene->camera);
		return (true);
	}
	return (false);
}
